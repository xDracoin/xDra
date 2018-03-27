# xDra Cold + Hot wallet MasterNode setup guide

> This is a community contributed guide. Feel free to suggest improvements via Issues or opening Pull Requests. Thank you!

## Requirements
* Windows 7 or higher, Mac OSX or linux with a wallet running (This will be your Cold wallet)
* Ubuntu 14.04 or 16.04 running on a VPS such as Vultr, or other server (This will be your Hot wallet) running 24/7
* Static IP Address
* Port 18053 port forwarded from your router to your Ubuntu server
* Basic Linux skills

---

## **Cold** Wallet Setup(Part 1) using the Qt GUI wallet on Windows, OSX, etc

This is the wallet where the MasterNode collateral of 5000 xDra coins will have to be transferred and stored.
After the setup is complete, this wallet doesn't have to run 24/7 and will be the one receiving the rewards.

### 1. Install and open the xDra-Qt wallet on your machine.

#### i.    Download the newest xDra-qt-{OS}-{version}.zip wallet from https://github.com/xDracoin/xDra/releases
#### ii.   Extract the xDra-qt.exe from xDra-qt-{OS}-{version}.zip (e.g. for Windows)
#### iii.  Start the new xDra-qt.exe
#### iv.   Click Run if you get a warning about an unverified publisher:
#### v.    If this is the first time you have started the wallet, you will be asked to enter a custom data directory. You can leave this default or change it to a directory that you want.
#### vi.   If this is the first time you have started the wallet, you will be asked to Allow Access by the firewall, click Allow access.
#### vii.  Let the wallet sync until you see the checkmark symbol in the lower right corner.
#### viii. Encrypt your wallet with a long passphrase and either save it in a password manager such as keepass, or write it down and keep it safe (in a locked compartment or safe) (recommended). This passphrase is your only key to your wallet, do NOT lose it or you will lose all your xDra. Do not let anyone steal your passcode or wallet either, just like in real life!
To encrypt the wallet, go to Settings > Encrypt wallet. Enter the passphrase, click ok. You will then have to restart the wallet and then go to Settings > Unlock Wallet and then enter the passphrase to unlock the wallet, for staking, controlling the masternode or sending your xDra.
#### ix.   Back up your wallet.dat in case of a mistake as soon as you encrypt your wallet. Once you have encrypted the wallet, your previous backups will not work, so back it up by going to File > Backup Wallet and save the backup to more than one place. Such as a USB key or a network share. I recommend keeping your wallet and passphrase seperate so that no one can steal both. They would need both to do anything to your wallet or xDra!

---

### 2. Create a receiving address for the Masternode collateral funds.

   Go to File -> Receiving addresses...
   
   Click **New**, type in a label (e.g. MN01) and press **Ok**.

### 3. Select the row of the newly added address and click **Copy** to store the destination address in the clipboard.
### 4. Send exactly 5000 xDra coins to the address you just copied. Double check you've got the correct address before transferring the funds.
     After sending, you can verify the balance in the Transactions tab. This can take a few minutes to be confirmed by the network.

### 5. Open the debug console of the wallet in order to type a few commands. 

   Go to `Tools` -> `Debug console`

### 6. Run the following command: `masternode genkey`

 You should see a long key that looks like:
   ```
   s3AvlaVoy9Tr8j64bRdhUc2qE4t6fLQ6EyePnMEkV1UXHqcRrG
   ```
   We will use this later on both cold and hot wallets.

### 7. Run `masternode outputs` command to retrieve the transaction ID of the collateral transfer.

   You should see an output that looks like this:
   ```
   [
      {
        "txhash" : "5e21q763e926c7cc0d2b2209e7eb93847039283eb595830942ebaf9037bb91ef",
        "outputidx" : 0
      }
   ]
   ```

   Both `txhash` and `outputidx` will be used in the next step. `outputidx` can be `0` or `1`, both are valid values
   
---

**!!!For anyone having issues with masternode outputs being blank!!!**
>If you have given the transaction a few minutes to get a confirmation and you still do not get any output from masternode outputs it means that you have not sent EXACTLY 5000 xDra in a single transaction. 
>To fix this, you do NOT need to send coins back to the exchange. You can send yourself coins from within your wallet. It is good practice to use a separate address for each masternode so that you can see the rewards from each masternode in a different address.
>So, follow the steps below. You can change the MN01 to MN02 for your 2nd masternode, etc. In fact, you can give the address any label that makes sense to you!

>Go to `Tools` -> `Debug console`
```
getnewaddress MN01
```
>A new address will be output. Copy the address.
```
sendtoaddress copied-address 5000
```
>Wait 1 minute
```
masternode outputs
```
>Done.

---

### 8. Go to `Tools` -> `Open Masternode Configuration File` and add a line in the newly opened `masternode.conf` file. 
> If you get prompted to choose a program, select notepad.exe to open it.

> This is an example of what you need in masternode.conf. Ignore any example text that may already be in there that contains a '#' in front of each line, that is just an example to help you. Read it if it helps.

> This is an example of masternode.conf
```
mn1 your_vps_ip_address:18053 your_masternode_key_output_from-masternode_genkey txhash_from-masternode_outputs Outputidx_from-masternode_outputs
```
> The file will contain an example that is commented out(with a # in front), but based on the above values, I would add this line in:
```
MN1 12.34.23.123:18053 s3AvlaVoy9Tr8j64bRdhUc2qE4t6fLQ6EyePnMEkV1UXHqcRrG 5e21q763e926c7cc0d2b2209e7eb93847039283eb595830942ebaf9037bb91ef 0
```
>   Where `12.34.23.123` is the external IP of the masternode server that will provide services to the network.

>   Where `s3AvlaVoy9Tr8j64bRdhUc2qE4t6fLQ6EyePnMEkV1UXHqcRrG` is your masternode key from `masternode genkey`.

>   Where `5e21q763e926c7cc0d2b2209e7eb93847039283eb595830942ebaf9037bb91ef` is your txhash from `masternode outputs`.

>   Where `0` is your outputidx from `masternode outputs`.
      
### 9. Restart the Qt wallet to pick up the `masternode.conf` changes.
### 10. Go to Masternodes tab and check if your newly added masternode is listed.
> If you want to control multiple hot wallets from this cold wallet, you will need to repeat the previous 2-10 steps. The `masternode.conf` file will contain an entry for each masternode that will be added to the network.

At this point, we are going to configure our remote Masternode server.


------


## **Hot** MasterNode VPS Setup(Part 2) with Linux CLI only wallet

Requires details from (Part 1).

This will run 24/7 and provide services to the network via TCP port 5500 for which it will be rewarded with coins. It will run with an empty wallet reducing the risk of loosing the funds in the event of an attack.

### 1. Get a VPS server from a provider like Vultr, DigitalOcean, Linode, Amazon AWS, etc. 

Requirements:
 * Linux VPS (**Ubuntu 16.04** 64 bit) - Choose the correct version for your OS from the release page
 * Dedicated Public IP Address
 * Recommended at least 1GB of RAM 

### 2. Login via SSH into the server and type the following command in the console:
**!! If you are logged in as root already, you can remove the prefix `sudo` at the commands in this part of the guide !!**

If you are using Windows, [PuTTY](https://putty.org) is a very good SSH client that you can use to connect to a remote Linux server.
If you are running a VPS from Vultr or similar, you need to use SSH such as putty if you want to copy and paste these commands otherwise you will have to type them all out!

Update and Install new packages by running these commands line by line *ONE* by *ONE*:

**!!!  Do not copy the entire thing and try to paste it, it will not work! Type or paste only one line at a time and hit enter after each line !!!**

```
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install wget nano unrar unzip libboost-all-dev libevent-dev software-properties-common -y
sudo add-apt-repository ppa:bitcoin/bitcoin -y
sudo apt-get update
sudo apt-get install libdb4.8-dev libdb4.8++-dev -y
```

### 3. Configure swap to avoid running out of memory:

```
sudo fallocate -l 1500M /mnt/1500MB.swap
sudo dd if=/dev/zero of=/mnt/1500MB.swap bs=1024 count=1572864
sudo mkswap /mnt/1500MB.swap
sudo swapon /mnt/1500MB.swap
sudo chmod 600 /mnt/1500MB.swap
sudo echo '/mnt/1500MB.swap  none  swap  sw 0  0' >> /etc/fstab
```

### 4. Allow the MasterNode p2p communication port through the OS firewall:

```
sudo ufw allow 22/tcp
sudo ufw limit 22/tcp
sudo ufw allow 18053/tcp
sudo ufw logging on
sudo ufw --force enable
```

If you are running the MasterNode server in Amazon AWS or another place where additional firewalls are in place, you need to allow incoming connections on port 18053/TCP



### 5. Install the xDra CLI wallet. Always download the latest [release available](https://github.com/xDracoin/xDra/releases). The file will be xDra-linux-cli.zip. Next, unpack it

If you are already running a `xDrad` on your server and want to upgrade it, stop the current one with:
```
xDrad stop
```
Run the following command until the xDrad process disappears.
```
ps aux | grep xDrad | grep -v grep
```

For **Ubuntu 16.04***

```
sudo apt-get install libzmq3-dev libminiupnpc-dev -y
wget https://github.com/xDracoin/xDra/releases/download/vx.x.x.x/xDra-linux-cli.zip
unzip xDra-linux-cli.zip
rm xDra-linux-cli.zip
chmod +x ./xDra-linux-cli/xDrad
sudo mv ./xDra-linux-cli/xDrad /usr/local/bin
cd ~
xDrad
```

You'll get a start error like `Error: To use xDrad, or the -server option to xDrad-qt, you must set an rpcpassword in the configuration file`. It's expected because we haven't created the config file yet.

The service will only start for a second and create the initial data directory(`~/.xDra/`).

### 6. Edit the MasterNode main wallet configuration file:
```
nano ~/.xDra/xDra.conf
```

Enter this wallet configuration data and change accordingly:
```
rpcuser=<alphanumeric_rpc_username>
rpcpassword=<alphanumeric_rpc_password>
rpcport=18054
listen=1
server=1
daemon=1
maxconnections=250
masternode=1
externalip=<ip_address_here>:18053
masternodeaddr=<ip_address_here>:18053
masternodeprivkey=<the_colw_wallet_genkey_value_here>
addnode=104.205.177.205:18053
addnode=109.106.139.185:18053
addnode=109.195.179.12:18053
addnode=109.95.229.159:18053
addnode=110.168.34.149:18053
addnode=113.180.106.60:18053
addnode=120.158.196.211:18053
addnode=144.217.90.42:18053
addnode=167.99.1.93:18053
addnode=173.176.95.92:18053
addnode=176.106.194.193:18053
addnode=176.210.199.81:18053
addnode=176.37.255.49:18053
addnode=178.140.46.42:18053
addnode=180.183.54.119:18053
addnode=185.107.64.202:18053
addnode=185.218.234.75:18053
addnode=188.116.128.51:18053
addnode=188.213.31.22:18053
addnode=188.234.213.132:18053
addnode=199.247.12.72:18053
addnode=217.182.173.104:18053
addnode=217.42.248.97:18053
addnode=218.57.95.62:18053
addnode=223.207.44.224:18053
addnode=37.14.32.165:18053
addnode=37.187.140.168:18053
addnode=37.79.203.164:18053
addnode=45.76.212.128:18053
addnode=46.161.2.92:18053
addnode=46.227.143.115:18053
addnode=46.4.88.76:4505
addnode=46.73.9.44:18053
addnode=47.139.54.235:18053
addnode=47.157.245.152:18053
addnode=49.0.68.10:18053
addnode=5.129.142.97:18053
addnode=5.65.84.84:18053
addnode=54.36.5.66:18053
addnode=54.39.66.152:18053
addnode=58.8.181.217:18053
addnode=71.187.236.176:18053
addnode=73.110.144.206:18053
addnode=77.68.213.55:18053
addnode=78.189.60.98:18053
addnode=78.36.193.51:18053
addnode=78.63.9.212:18053
addnode=79.20.96.89:18053
addnode=80.212.158.47:18053
addnode=82.64.3.134:18053
addnode=84.244.7.219:18053
addnode=84.55.45.14:18053
addnode=85.106.13.210:18053
addnode=85.15.94.1:18053
addnode=85.95.182.114:18053
addnode=86.10.46.26:18053
addnode=88.99.201.58:4505
addnode=89.243.150.165:18053
addnode=90.100.26.38:18053
addnode=94.180.238.198:18053
addnode=94.249.192.89:18053
addnode=95.79.50.147:18053
addnode=95.89.45.93:18053
addnode=97.103.17.167:18053
```
You can right click in SHH (putty) to paste all of the above

Exit the editor by CTRL+X and hit Y + ENTER to commit your changes.

This is a real example, based on the `genkey` obtained in the Cold(Part 1) wallet section:
```
rpcuser=xDrarpc
rpcpassword=SeCurePassword23jkm32hkj23h423jkh324
rpcport=18054
listen=1
server=1
daemon=1
maxconnections=250
masternode=1
externalip=12.34.23.123:18053
masternodeaddr=12.34.23.123:18053
masternodeprivkey=s3AvlaVoy9Tr8j64bRdhUc2qE4t6fLQ6EyePnMEkV1UXHqcRrG
addnode=104.205.177.205:18053
addnode=109.106.139.185:18053
addnode=109.195.179.12:18053
addnode=109.95.229.159:18053
addnode=110.168.34.149:18053
addnode=113.180.106.60:18053
addnode=120.158.196.211:18053
addnode=144.217.90.42:18053
addnode=167.99.1.93:18053
addnode=173.176.95.92:18053
addnode=176.106.194.193:18053
addnode=176.210.199.81:18053
addnode=176.37.255.49:18053
addnode=178.140.46.42:18053
addnode=180.183.54.119:18053
addnode=185.107.64.202:18053
addnode=185.218.234.75:18053
addnode=188.116.128.51:18053
addnode=188.213.31.22:18053
addnode=188.234.213.132:18053
addnode=199.247.12.72:18053
addnode=217.182.173.104:18053
addnode=217.42.248.97:18053
addnode=218.57.95.62:18053
addnode=223.207.44.224:18053
addnode=37.14.32.165:18053
addnode=37.187.140.168:18053
addnode=37.79.203.164:18053
addnode=45.76.212.128:18053
addnode=46.161.2.92:18053
addnode=46.227.143.115:18053
addnode=46.4.88.76:4505
addnode=46.73.9.44:18053
addnode=47.139.54.235:18053
addnode=47.157.245.152:18053
addnode=49.0.68.10:18053
addnode=5.129.142.97:18053
addnode=5.65.84.84:18053
addnode=54.36.5.66:18053
addnode=54.39.66.152:18053
addnode=58.8.181.217:18053
addnode=71.187.236.176:18053
addnode=73.110.144.206:18053
addnode=77.68.213.55:18053
addnode=78.189.60.98:18053
addnode=78.36.193.51:18053
addnode=78.63.9.212:18053
addnode=79.20.96.89:18053
addnode=80.212.158.47:18053
addnode=82.64.3.134:18053
addnode=84.244.7.219:18053
addnode=84.55.45.14:18053
addnode=85.106.13.210:18053
addnode=85.15.94.1:18053
addnode=85.95.182.114:18053
addnode=86.10.46.26:18053
addnode=88.99.201.58:4505
addnode=89.243.150.165:18053
addnode=90.100.26.38:18053
addnode=94.180.238.198:18053
addnode=94.249.192.89:18053
addnode=95.79.50.147:18053
addnode=95.89.45.93:18053
addnode=97.103.17.167:18053
```

The IP address(`12.34.23.123` in this example) will be different for you. Use the `ifconfig` command to find out your IP address, normally the address of the `eth0` interface.
Same goes for the `masternodeprivkey` value. You need the key returned by the `masternode genkey` command executed in the Cold Wallet(Part 1). The exact same key needs to be used for the masternode entry in the `masternode.conf` file of your Cold Wallet(Part 1)


### 7. Start the service with:
```
xDrad
```

### 8. Wait until is synced with the blockchain network:
Run this command every few mins until the block count stopped increasing fast.
```
xDrad getinfo
``` 
Give it 30 mins now for this node to "get social" with the other nodes in the network. Once it peers up with a good number of other masternodes, the following activation steps should work fine.


## Enable the Masternode

### 1. Go back to the local(cold) wallet and open `Tools` > `Debug console`.

Type this command to see all the MasterNodes loaded from the `masternode.conf` file with their current status:
```
masternode list-conf
```

You should now see the newly added MasterNode with a status of `MISSING`.

Run the following command, in order to enable it:
```
masternode start-alias MN01
```
In this ^ case, the alias of my MasterNode was MN01, in your case, it might be different.


### 2. Verify that the MasterNode is enabled and contributing to the network.

Give it a few minutes and go to the Linux VPS console and check the status of the masternode with this command:
```
xDrad masternode status
```

If you see status `Masternode successfully started`, you've done it, congratulations. Go hug someone now :)
It will take a few hours until the first rewards start coming in.

Instead, if you get status `Masternode not found in the list of available masternodes`, you need a bit more patience. Distributed systems take a bit of time to reach consensus. Restarting the wallets and retrying the start has been reported to help by community members. This is how you restart the Linux wallet from the CLI:
```
xDrad stop
```
Run the following command until the xDrad process disappears.
```
ps aux | grep oind | grep -v grep
```
Then run the daemon.
```
xDrad
```
Rerun the `startmasternode` command again in the Qt (Cold) wallet.

The masternode debug log (`~/.xDra/debug.log`) will contain this line on a successful activation:
```
2018-02-02 02:07:12 CActiveMasternode::EnableHotColdMasterNode() - Enabled! You may shut down the cold daemon.
```
You can watch the log as it's being written by using this command:
```
tail -f ~/.xDra/debug.log
```
Stop watching the log by pressing CTRL+C

As the log entry says, your MasterNode is up and running and the hot wallet that holds the collateral can be closed without impacting the operation of the MasterNode in the network.

You should now be able to see your MasterNode(s) in your wallet under the masternodes tab.

Cheers !