# consumer_bollinger.py
from kafka import KafkaConsumer, KafkaProducer
import pandas as pd
import json

consumer = KafkaConsumer(
    'stock_prices',
    bootstrap_servers=['localhost:9092'],
    value_deserializer=lambda v: json.loads(v.decode('utf-8')),
    group_id='analytics-group'
)

producer = KafkaProducer(
    bootstrap_servers=['localhost:9092'],
    value_serializer=lambda v: json.dumps(v).encode('utf-8')
)

def compute_bollinger(prices, window=20):
    df = pd.DataFrame(prices, columns=['close']) # list to pandas
    # moving average - standard dev 
    df['MA'] = df['close'].rolling(window=window).mean()
    df['STD'] = df['close'].rolling(window=window).std()
    # get upper and lower Bollinger Band
    df['Upper'] = df['MA'] + (df['STD'] * 2)
    df['Lower'] = df['MA'] - (df['STD'] * 2)
    return df.iloc[-1].to_dict()

prices = []
for msg in consumer:
    price = msg.value['close']
    prices.append(price)
    if len(prices) >= 20:
        # calculate after getting 20 
        result = compute_bollinger(prices[-20:])
        producer.send("bollinger_bands", result)
        print("Computed:", result)







