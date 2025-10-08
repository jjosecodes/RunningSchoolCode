from fastapi import FastAPI
from fastapi.responses import StreamingResponse
import requests
import json
import time
from datetime import datetime, timedelta

app = FastAPI()

# ==============================================
# CONFIGURATION
# ==============================================
MYAPI_URL = "https://data.alpaca.markets/v2/stocks/AAPL/bars"  # Alpaca endpoint
MYAPI_KEY = "YOUR_ALPACA_API_KEY"
MYAPI_SECRET = "YOUR_ALPACA_SECRET_KEY"

# ==============================================
# FETCH 1-MINUTE DATA FROM ALPACA (MYAPI)
# ==============================================
def fetch_minute_data(symbol: str = "AAPL", limit: int = 3):
    """
    Fetch recent 1-minute candles for a given symbol from Alpaca.
    """
    headers = {
        "APCA-API-KEY-ID": MYAPI_KEY,
        "APCA-API-SECRET-KEY": MYAPI_SECRET,
    }

    params = {
        "timeframe": "1Min",
        "limit": limit,
    }

    response = requests.get(f"{MYAPI_URL}?symbol={symbol}", headers=headers, params=params)

    if response.status_code != 200:
        raise RuntimeError(f"API Error {response.status_code}: {response.text}")

    data = response.json()

    # Alpaca’s format: {"bars": [{"t": "...", "o": ..., "h": ..., "l": ..., "c": ..., "v": ...}, ...]}
    bars = data.get("bars", [])
    return [
        {
            "symbol": symbol,
            "timestamp": bar["t"],
            "open": bar["o"],
            "high": bar["h"],
            "low": bar["l"],
            "close": bar["c"],
            "volume": bar["v"],
        }
        for bar in bars
    ]

# ==============================================
# SIMULATE SECOND-BY-SECOND TICKS
# ==============================================
def simulate_second_by_second(minute_data):
    for minute in minute_data:
        open_price = minute["open"]
        close_price = minute["close"]
        diff = (close_price - open_price) / 60.0

        for sec in range(60):
            tick = {
                "symbol": minute["symbol"],
                "timestamp": datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"),
                "price": round(open_price + diff * sec, 2)
            }

            # Stream 
            yield f"data: {json.dumps(tick)}\n\n"
            time.sleep(1) # 1 second per tick

# ==============================================
# FASTAPI ENDPOINT
# ==============================================
@app.get("/stream/{symbol}")
def stream_data(symbol: str):
    """
    Fetch minute-by-minute data for a stock and simulate second stream.
    """
    try:
        minute_data = fetch_minute_data(symbol)
    except Exception as e:
        return {"error": str(e)}

    return StreamingResponse(simulate_second_by_second(minute_data), media_type="text/event-stream")
