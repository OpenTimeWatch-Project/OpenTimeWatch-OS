# OpenTimeWatchOS Configurator Tool

print("Welcome to OpenTimeWatchOS configuration script")
OSVarPath = "src/osVariables/osVariables.cpp"
OSConfPath = "platformio.ini"

def configureBoard(userBoard):
    if userBoard == 1:
      try:
        with open(OSConfPath, 'r') as file:
                lines = file.readlines()
        for i, line in enumerate(lines):
            if i == 6:  # Uncomment line 7
               lines[i] = line.lstrip(";")
            elif i == 5:  # Comment line 6
                if not line.startswith(";"):
                   lines[i] = ";" + line
            elif i == 10:  # Uncomment line 11
                lines[i] = line.lstrip(";")
            elif i == 9:  # Comment line 10
                if not line.startswith(";"):
                   lines[i] = ";" + line
            elif i == 15:  # Uncomment line 16
                lines[i] = line.lstrip(";")
        with open(OSConfPath, 'w') as file:
            file.writelines(lines)         
      except Exception as e:
        print(f"An error occurred: {e}")
    
    else:
      try:
        with open(OSConfPath, 'r') as file:
                lines = file.readlines()
        for i, line in enumerate(lines):
            if i == 5:  # Uncomment line 6
               lines[i] = line.lstrip(";")
            elif i == 6:  # Comment line 7
                if not line.startswith(";"):
                   lines[i] = ";" + line
            elif i == 9:  # Uncomment line 10
                lines[i] = line.lstrip(";")
            elif i == 10:  # Comment line 11
                if not line.startswith(";"):
                   lines[i] = ";" + line
            elif i == 15:  # Comment line 16
                if not line.startswith(";"):
                   lines[i] = ";" + line
        with open(OSConfPath, 'w') as file:
            file.writelines(lines)         
      except Exception as e:
        print(f"An error occurred: {e}")


def configureWifiNetwork(userSSID):
    try:
        with open(OSVarPath, 'r') as file:
            lines = file.readlines()

        with open(OSVarPath, 'w') as file:
            for line in lines:
                if 'const char* ssid = ' in line:
                    line = f'const char* ssid  = "{userSSID}";\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")

def configureWifiPassword(userPassword):
    try:
        with open(OSVarPath, 'r') as file:
            lines = file.readlines()

        with open(OSVarPath, 'w') as file:
            for line in lines:
                if 'const char* password = ' in line:
                    line = f'const char* password = "{userPassword}";\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")
    
def configureGMTOffset(userGMT):
    try:
        with open(OSVarPath, 'r') as file:
            lines = file.readlines()

        with open(OSVarPath, 'w') as file:
            for line in lines:
                if 'const long gmtOffset_sec = ' in line:
                    line = f'const long  gmtOffset_sec = {userGMT};\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")

def configureDayLightOffset(userDayLight):
    try:
        with open(OSVarPath, 'r') as file:
            lines = file.readlines()

        with open(OSVarPath, 'w') as file:
            for line in lines:
                if 'const int daylightOffset_sec = ' in line:
                    line = f'const int daylightOffset_sec = {userDayLight};\n'
                file.write(line)
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    print("1. Configure")
    print("2. About")
    print("3. Exit")
    userOption = input("Select an option: ")

    if userOption == "1":
        print("Watch Hardware: ")
        print("1. T-QT-Pro-N4R2")
        print("2. T-QT-Pro-N8")
        userBoard = int(input("Select your board: "))
        configureBoard(userBoard)
        if userBoard == 1:
            print("You have selected T-QT-Pro-N8")
        else:
            print("You have selected T-QT-Pro-N4R2")
        userSSID = input("Enter your WiFi network name: ")
        configureWifiNetwork(userSSID)
        userPassword = input("Enter your WiFi network password: ")
        configureWifiPassword(userPassword)
        userGMT = input("Enter your area's GMT offset(in seconds): ")
        configureGMTOffset(userGMT)
        userDayLight = input("Enter your area's day light offset(in seconds): ")
        configureDayLightOffset(userDayLight)
        print("Configuration complete. Please upload the code.")
    elif userOption == "2":
        print("OpenTimeWatchOS Configuration Script V1.1")
        print("This is a configuration script for OpenTimeWatchOS for your watch hardware")
        print("It allows you to configure the Board, WiFi SSID, password, GMT offset, and daylight offset")
        print("For more information, visit the OpenTimeWatchOS GitHub repository.")
        print("https://github.com/OpenTimeWatch-Project/OpenTimeWatch-OS")
    elif userOption == "3":
        print("Exiting the script. Goodbye!")
        exit(0)
    else:
        print("Invalid option. Please try again.")
        exit(1)
