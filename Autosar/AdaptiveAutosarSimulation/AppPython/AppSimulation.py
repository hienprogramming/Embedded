import tkinter as tk
from tkinter import ttk
import socket
import threading


class SteeringApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Steering Wheel Simulator")
        self.root.geometry("400x400")
        self.root.resizable(False, False)

        # Variables
        self.steering_angle = tk.DoubleVar(value=0)  # Steering angle (-90 to 90)
        self.position = tk.DoubleVar(value=0)       # Position (-10 to 10)

        # Title Label
        title_label = tk.Label(root, text="Steering Wheel Simulator", font=("Arial", 16, "bold"))
        title_label.pack(pady=10)

        # Steering Angle Section
        steering_frame = tk.Frame(root)
        steering_frame.pack(pady=20)

        steering_label = tk.Label(steering_frame, text="Steering Angle (degree angle):", font=("Arial", 12))
        steering_label.pack(side=tk.LEFT, padx=5)

        self.steering_value_label = tk.Label(steering_frame, text="0degree angle", font=("Arial", 12, "bold"), fg="blue")
        self.steering_value_label.pack(side=tk.LEFT)

        steering_slider = ttk.Scale(
            root, from_=-90, to=90, variable=self.steering_angle, orient="horizontal",
            length=300, command=self.update_steering
        )
        steering_slider.pack(pady=10)

        # Position Section
        position_frame = tk.Frame(root)
        position_frame.pack(pady=20)

        position_label = tk.Label(position_frame, text="Position (m):", font=("Arial", 12))
        position_label.pack(side=tk.LEFT, padx=5)

        self.position_value_label = tk.Label(position_frame, text="0 m", font=("Arial", 12, "bold"), fg="green")
        self.position_value_label.pack(side=tk.LEFT)

        position_slider = ttk.Scale(
            root, from_=-10, to=10, variable=self.position, orient="horizontal",
            length=300, command=self.update_position
        )
        position_slider.pack(pady=10)

        # Display Data Button
        self.data_label = tk.Label(root, text="Data: Steering = 0degree angle, Position = 0 m", font=("Arial", 12))
        self.data_label.pack(pady=20)

        update_button = tk.Button(root, text="Start Sending Data", command=self.start_sending_data, font=("Arial", 12))
        update_button.pack(pady=10)

        self.running = False  # To control the socket thread

    def update_steering(self, _=None):
        """Update steering angle display."""
        angle = self.steering_angle.get()
        self.steering_value_label.config(text=f"{angle:.1f}degree angle")

    def update_position(self, _=None):
        """Update position display."""
        pos = self.position.get()
        self.position_value_label.config(text=f"{pos:.1f} m")

    def start_sending_data(self):
        """Start a thread to send data via socket."""
        self.running = True
        threading.Thread(target=self.send_data, daemon=True).start()

    # def send_data(self):
    #     """Send steering and position data to C++ via socket."""
    #     host = '127.0.0.1'  # Localhost
    #     port = 65432        # Port to listen on

    #     while self.running:
    #         try:
    #             with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
    #                 server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    #                 server.bind((host, port))
    #                 server.listen(1)
    #                 print("Waiting for connection...")
    #                 conn, addr = server.accept()
    #                 print(f"Connected to {addr}")

    #                 with conn:
    #                     while self.running:
    #                         # Prepare data
    #                         angle = self.steering_angle.get()
    #                         pos = self.position.get()
    #                         data = f"{angle:.2f},{pos:.2f}"  # Format: "steering,position"
    #                         conn.sendall(data.encode('utf-8'))  # Send data
    #                         print(f"Sent: {data}")
    #                         self.root.after(100)  # Wait for 100ms before sending next data
    #         except (BrokenPipeError, ConnectionResetError) as e:
    #             print(f"Connection error: {e}. Retrying...")
    #         except Exception as e:
    #             print(f"Unexpected error: {e}")

    def send_data(self):
        """Send steering and position data to C++ via socket."""
        host = '127.0.0.1'  # Localhost
        port = 65432        # Port to listen on

        while self.running:
            try:
                with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
                    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                    server.bind((host, port))
                    server.listen(1)
                    self.data_label.config(text="Waiting for connection...", fg="red")
                    print("Waiting for connection...")
                    conn, addr = server.accept()
                    print(f"Connected to {addr}")
                    self.data_label.config(text=f"Connected to {addr}", fg="green")

                    with conn:
                        while self.running:
                            # Prepare data
                            angle = self.steering_angle.get()
                            pos = self.position.get()
                            data = f"{angle:.2f},{pos:.2f}"  # Format: "steering,position"
                            conn.sendall(data.encode('utf-8'))  # Send data
                            print(f"Sent: {data}")
                            self.root.after(100)  # Wait for 100ms before sending next data
            except (BrokenPipeError, ConnectionResetError):
                self.data_label.config(text="Client disconnected. Retrying...", fg="orange")
                print("Client disconnected. Waiting for a new connection...")
            except Exception as e:
                print(f"Unexpected error: {e}")


    def stop_sending_data(self):
        """Stop the socket thread."""
        self.running = False


# Main application
if __name__ == "__main__":
    root = tk.Tk()
    app = SteeringApp(root)

    # Graceful shutdown on closing the app
    def on_closing():
        app.stop_sending_data()
        root.destroy()

    root.protocol("WM_DELETE_WINDOW", on_closing)
    root.mainloop()
