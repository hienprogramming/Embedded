# File: acc_client.py
import socket
import time
import math
import pandas as pd
from datetime import datetime
import os
import json

def calculate_new_speed(front_speed, our_speed, gap, safe_gap=20.0, dt=1.0, 
                          max_deceleration=3.0, acceleration=1.0, desired_speed=30.0):
    if gap < safe_gap and our_speed > front_speed:
        required_decel = (our_speed**2 - front_speed**2) / (2 * (safe_gap - gap)) if (safe_gap - gap) != 0 else max_deceleration
        required_decel = min(required_decel, max_deceleration)
        new_speed = our_speed - required_decel * dt
        if new_speed < front_speed:
            new_speed = front_speed
    elif gap >= safe_gap and our_speed < desired_speed:
        new_speed = our_speed + acceleration * dt
        new_speed = min(new_speed, desired_speed)
    else:
        new_speed = our_speed
    return new_speed

def main():
    host = '127.0.0.1'
    port = 12345

    # Initialize data storage
    data_records = []
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(1.0)
    s.connect((host, port))
    
    print("Connected to server. Waiting for data...")
    
    while True:
        try:
            data = s.recv(1024)
            if not data:
                break
            
            decoded = data.decode('utf-8')
            parts = decoded.split(',')
            if len(parts) < 3:
                continue
            front_speed = float(parts[0])
            our_speed = float(parts[1])
            gap = float(parts[2])
            print(f"Received: front_speed={front_speed:.2f} m/s, our_speed={our_speed:.2f} m/s, gap={gap:.2f} m")
            
            new_speed = calculate_new_speed(front_speed, our_speed, gap)
            print(f"Calculated new speed: {new_speed:.2f} m/s")
            
            # Record data
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            data_records.append({
                'Timestamp': timestamp,
                'Front Speed (m/s)': front_speed,
                'Our Speed (m/s)': our_speed,
                'Gap (m)': gap,
                'Calculated Speed (m/s)': new_speed
            })
            
            s.send(str(new_speed).encode('utf-8'))
            
        except socket.timeout:
            print("Waiting for server data...")
            continue
        except Exception as e:
            print("Error:", e)
            break
        
        time.sleep(1)

    # Save data to Excel file
    # if data_records:
    #     try:
    #         df = pd.DataFrame(data_records)
    #         # Create a 'data' folder if it doesn't exist
    #         os.makedirs('data', exist_ok=True)
            
    #         filename = os.path.join('data', f'acc_data_{datetime.now().strftime("%Y%m%d_%H%M%S")}.xlsx')
    #         df.to_excel(filename, index=False)
    #         print(f"Data saved to {filename}")
    #     except PermissionError:
    #         # Try with a different filename if the first attempt fails
    #         try:
    #             alt_filename = os.path.join('data', f'acc_data_backup_{datetime.now().strftime("%Y%m%d_%H%M%S%f")}.xlsx')
    #             df.to_excel(alt_filename, index=False)
    #             print(f"Data saved to alternative file: {alt_filename}")
    #         except Exception as e:
    #             print(f"Failed to save data to Excel: {e}")
    #             # Fallback to CSV if Excel fails
    #             csv_filename = os.path.join('data', f'acc_data_{datetime.now().strftime("%Y%m%d_%H%M%S")}.csv')
    #             try:
    #                 df.to_csv(csv_filename, index=False)
    #                 print(f"Data saved to CSV instead: {csv_filename}")
    #             except Exception as e:
    #                 print(f"Failed to save data completely: {e}")
    #     except Exception as e:
    #         print(f"Error saving data: {e}")

    # Save data to JSON file
    if data_records:
        try:
            # Create a 'data' folder if it doesn't exist
            os.makedirs('data', exist_ok=True)
            
            json_filename = os.path.join('data', f'acc_data_{datetime.now().strftime("%Y%m%d_%H%M%S")}.json')
            with open(json_filename, 'w') as json_file:
                json.dump(data_records, json_file, indent=4)
            print(f"Data saved to JSON file: {json_filename}")
        except Exception as e:
            print(f"Error saving data to JSON: {e}")

    s.close()

if __name__ == '__main__':
    main()