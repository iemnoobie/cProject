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

             # Check if 'mac' key exists in addresses before accessing
            if 'mac' in scanner[host]['addresses']:
                mac_address = scanner[host]['addresses']['mac']
                result_text.insert(tk.END, f"MAC Address: {mac_address}\n")

                # Check if 'vendor' key exists before accessing vendor data
                if 'vendor' in scanner[host] and mac_address in scanner[host]['vendor']:
                    result_text.insert(tk.END, f"Vendor: {scanner[host]['vendor'][mac_address]}\n")
                else:
                    result_text.insert(tk.END, "Vendor: Unknown\n")
            else:
                result_text.insert(tk.END, "MAC Address: Not Available\n")


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
