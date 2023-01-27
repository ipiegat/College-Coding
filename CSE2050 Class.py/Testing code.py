pairs = {"Sun":"Sunday", "Mon": "Monday", "Tue": "Tuesday", "Wedn": "Wednesday", "Thur":"Thursday", "Fri": "Friday", "Satu": "Saturday"}

class DaysOfTheWeek:
    def __init__(self, abbreviated_name):
        self.abbreviated_name = abbreviated_name
    
    def full_name(self):
        return pairs[self.abbreviated_name]
    
Day = DaysOfTheWeek("Sun")
print(Day.full_name())