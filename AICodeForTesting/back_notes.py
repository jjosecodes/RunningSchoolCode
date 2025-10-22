# producer_redis.py
from fastapi import FastAPI, Request
import redis
import json

app = FastAPI()
r = redis.Redis(host="localhost", port=6379, db=0)

@app.post("/send_stock")
async def send_stock(request: Request):
    data = await request.json()
    # {"symbol": "AAPL", "close": 179.23,
    #"timestamp": "2025-10-06T10:00:00Z"}
    r.xadd("stock_prices", {"data": json.dumps(data)})
    return {"status": "sent", "data": data}





