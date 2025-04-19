# Program to update the WiFi SSID in main.cpp

print("Welcome to OpenTimeWatchOS configuration script")
file_path = "/home/jaswanth/Developer/Arduino/OpenTimeWatch-OS/src/osVariables/osVariables.cpp"

def configureWifiNetwork(userSSID):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()

        with open(file_path, 'w') as file:
            for line in lines:
                if 'const char* ssid = ' in line:
                    line = f'const char* ssid  = "{userSSID}";\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")

def configureWifiPassword(userPassword):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()

        with open(file_path, 'w') as file:
            for line in lines:
                if 'const char* password = ' in line:
                    line = f'const char* password = "{userPassword}";\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")
    
def configureGMTOffset(userGMT):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()

        with open(file_path, 'w') as file:
            for line in lines:
                if 'const long gmtOffset_sec = ' in line:
                    line = f'const long  gmtOffset_sec = {userGMT};\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")

def configureDayLightOffset(userDayLight):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()

        with open(file_path, 'w') as file:
            for line in lines:
                if 'const int daylightOffset_sec = ' in line:
                    line = f'const int daylightOffset_sec = {userDayLight};\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    
    userSSID = input("Enter your WiFi network name: ")
    configureWifiNetwork(userSSID)
    userPassword = input("Enter your WiFi network password: ")
    configureWifiPassword(userPassword)
    userGMT = input("Enter your area's GMT offset(in seconds): ")
    configureGMTOffset(userGMT)
    userDayLight = input("Enter your area's day light offset(in seconds): ")
    configureDayLightOffset(userDayLight)
    
print("Configuration complete. Please upload the code.")