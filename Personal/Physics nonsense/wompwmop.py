import math

x1 = 120*(math.cos(60))
x2 = 80*(math.cos(75))

y1 = 120*(math.sin(60))
y2 = 80*(math.sin(75))

x_total = x2 - x1
y_total = y2 - y1

angle = math.tan(x_total/y_total)
magnitude = math.sqrt((x_total)**2+(y_total)**2)


print(f'{magnitude} newtons\n{angle} degrees')




