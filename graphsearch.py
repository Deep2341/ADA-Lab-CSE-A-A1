import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("binary_search_time.csv")
plt.plot(data['n'], data['Time(seconds)'], marker='o', color='green')
plt.xlabel('Number of Elements (n)')
plt.ylabel('Time Taken (seconds)')
plt.title('Time vs. Number of Elements (Binary Search)')
plt.grid(True)
plt.show()
