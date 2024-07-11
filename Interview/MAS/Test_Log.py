# example.py
import time

def log_event(event_id, data):
    timestamp = time.strftime("%a %b %d %H:%M:%S %Y")
    print(f"Event ID: {event_id}")
    print(f"Timestamp: {timestamp}")
    print(f"Data: {data}")
    print("-" * 24)

def main():
    events = [
        (1, "Engine start"),
        (2, "Speed: 60 km/h"),
        (3, "Brake applied"),
        (4, "Accident detected: Front collision")
    ]
    
    for event_id, data in events:
        log_event(event_id, data)
        time.sleep(1)  # Giả lập thời gian giữa các sự kiện

if __name__ == "__main__":
    main()