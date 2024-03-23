import subprocess
import select
import os

mapping = {}
mapping[20] = "✔"
mapping[24] = "✘"

def tail_kern_log():
    # Execute 'sudo tail -f /var/log/kern.log' as a subprocess
    process = subprocess.Popen(['sudo', 'tail', '-f', '/var/log/kern.log'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # Continuously monitor the output of the tail command
    while True:
        # Use select to wait for data to become available on stdout
        ready, _, _ = select.select([process.stdout], [], [])

        # If stdout has data available, read and print it
        if process.stdout in ready:
            new_log = process.stdout.readline().decode('utf-8')  # Read the new log line
            string = new_log.strip()  # Print the new log, stripping any trailing newline characters
            if "New key pressed" in string:
                print(string)
                try:
                    with open("keyboard.txt", "r") as file:
                        name = file.read()
                        name=ord(name[0])
                        try:
                            string=mapping[name]
                        except:
                            string=chr(name)
                        print(string)
                        with open("keyboard.txt", "w") as file:
                            file.write(string)
                except:
                    print('',end='')

tail_kern_log()
