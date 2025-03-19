import tkinter as tk
from tkinter import messagebox, scrolledtext
import nmap


def scan_network():
    ip_range = ip_entry.get()

    if not ip_range:
        messagebox.showerror("Error", "Please enter a valid IP range.")
        return

    scanner = nmap.PortScanner()
    result_text.delete(1.0, tk.END)

    try:
        result_text.insert(tk.END, f"Scanning IP range: {ip_range}\n")
        scanner.scan(hosts=ip_range, arguments='-sn')

        for host in scanner.all_hosts():
            result_text.insert(tk.END, f"\nHost: {host} ({scanner[host].hostname()})\n")
            result_text.insert(tk.END, f"State: {scanner[host].state()}\n")

            if 'mac' in scanner[host]['addresses']:
                result_text.insert(tk.END, f"MAC Address: {scanner[host]['addresses']['mac']}\n")

            if 'vendor' in scanner[host]:
                result_text.insert(tk.END, f"Vendor: {scanner[host]['vendor'].get(scanner[host]['addresses']['mac'], 'Unknown')}\n")

    except Exception as e:
        messagebox.showerror("Error", f"An error occurred: {e}")


# GUI Setup
root = tk.Tk()
root.title("Network Scanner")
root.geometry("600x400")

# IP Range Entry
tk.Label(root, text="Enter IP Range (e.g., 192.168.1.0/24):").pack(pady=5)
ip_entry = tk.Entry(root, width=40)
ip_entry.pack(pady=5)

# Scan Button
scan_button = tk.Button(root, text="Scan", command=scan_network)
scan_button.pack(pady=10)

# Results Display
result_text = scrolledtext.ScrolledText(root, width=70, height=15)
result_text.pack(pady=10)

# Run GUI
root.mainloop()
