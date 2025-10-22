# sample_stock_data.py
import json
import time

data_points = [
    {"symbol": "AAPL", "close": 179.23, "timestamp": "2025-09-29T10:00:00Z"},
    {"symbol": "AAPL", "close": 180.12, "timestamp": "2025-09-29T10:01:00Z"},
    {"symbol": "AAPL", "close": 181.04, "timestamp": "2025-09-29T10:02:00Z"},
    {"symbol": "AAPL", "close": 179.90, "timestamp": "2025-09-29T10:03:00Z"},
]

for point in data_points:
    print(json.dumps(point, indent=2))
    time.sleep(1)  # Simulate 1-second intervals