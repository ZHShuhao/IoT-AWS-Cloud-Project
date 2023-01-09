# ioT_Project
This is a ioT project about design of DHT22 Temperature and humidity, AWS Cloud and Webpage

# Project background
Internet of Things (IoT) refers to the real-time collection of any object or process that needs monitoring, connection and interaction through various devices and technologies such as various information sensors.As one of the low-power wide-area network communication technologies, LoRa can achieve characteristics that cannot be realized by traditional wireless sensor networks—at the same time, it has the advantages of long transmission distance and low power consumption.During the cold chain transportation, incorrect temperature can cause very serious financial loss. With the development of Internet of Things technology. The data of the current environment can be obtained in real time and uploaded to the cloud for analysis and monitoring.

<img width="552" alt="image" src="https://user-images.githubusercontent.com/89632568/211413338-b7799843-84b7-4cdf-9b54-714a147ed1e7.png">
<img width="521" alt="image" src="https://user-images.githubusercontent.com/89632568/211413378-9b3fdfe6-34c5-445e-8055-39c5386d1175.png">

# 1. How to connect DHT22 Tempurature and humidity sensor to ESP32 LoRa borad
## physical connection

<img width="505" alt="image" src="https://user-images.githubusercontent.com/89632568/211405753-73eb41be-48b0-4e9f-a1a5-f449067d0b04.png">

## Software config

Using PlateformIO in the VSCode developer tool, install the corresponding development library. In this project we use the AWS_IOT library to connect to AWS cloud, Audrino library to config ESP32 development board; DHT22 library to connect DHT22 sensor and MYSQL library to store environment data.

<img width="647" alt="image" src="https://user-images.githubusercontent.com/89632568/211406394-47183c04-b2b2-47a3-84b7-0376f650f9ca.png">

There are lots of office thrild library can be used directely to developt ESP32 board.

# 2. Config AWS
Open the AWS cloud and create virtual things corresponding to the devices of real world. 

<img width="806" alt="image" src="https://user-images.githubusercontent.com/89632568/211407314-b6a5f500-d27c-4a15-93ba-54e0deb7960a.png">

# 3. LoRa protocol
<img width="1066" alt="image" src="https://user-images.githubusercontent.com/89632568/211407886-68ed8769-882f-4e18-a56d-57923358a1ef.png">

LoRa is a low-power, long-range, wireless, wide-area network standard created by semtech.

Working frequency: ISM frequency band includes 433, 868, 915 MH, etc.

# 4. MQTT protocol.
MQTT is a lightweight message transmission protocol based on the publish/subscribe model. It is specially designed for IoT applications in low-bandwidth and unstable network environments. It can provide real-time and reliable message services for networked devices with very little code. Simple and easy to implement

# 5. Project Architeture
In this IoT project, we implement two ways to connect to AWS. Implementation 1 uses both LoRa and MQTT protocols. DHT22 sent the environment data to the ESP32 board directly, then the end-node  ESP32 board processed and send data to another ESP32 board that connect to the internet. When the ESP32 board which is connected to the internet receive the data from end nodes successfully, it sends these data through the MQTT protocol to the AWS cloud and store data in the MYSQL database.
At last, users can check environment data through different end-node devices like Ipad, Phones, and laptops. What's more, users can observe the time-to-time change of data by browsing the line chart on the web page.
<img width="1219" alt="image" src="https://user-images.githubusercontent.com/89632568/211413901-4c5d0f0e-4720-47d2-94eb-3720015490a2.png">

Implementation 2 implements three end nodes that connect to AWS directly and independently. Three end nodes send environment data to the AWS cloud directly through the MQTT protocol.
 
<img width="1234" alt="image" src="https://user-images.githubusercontent.com/89632568/211413845-09dd4b91-6ec3-439c-af0c-6de2556921ba.png">


# How devices connect to the AWS
If want devices to join the AWS, every device needs a certificate from AWS. Now we will config the certificate for devices. Download the CA root certificate, public key,and private key. For the ESP32 development board, we need to use code to config the certificate.

Download the certificate from the AWS web page.
<img width="657" alt="image" src="https://user-images.githubusercontent.com/89632568/211411873-2053d41a-7de3-4026-8df3-b068d4be3cfc.png">
<img width="427" alt="image" src="https://user-images.githubusercontent.com/89632568/211411919-595ee635-2a33-47c1-b170-9420f34b3764.png">

Config certificate for ESP32 development board.
<img width="775" alt="image" src="https://user-images.githubusercontent.com/89632568/211416221-75769527-ada9-492a-a831-2174058192e2.png">

# Show & Analyz data
Data will be sent to AWS and stored in the MySQL database. Users can choose the way in which they like to observe the temperature and humidity data, at the same time, users can also observe time-to-time changes of data by browsing the line chart on the web page.
<img width="1235" alt="image" src="https://user-images.githubusercontent.com/89632568/211413038-6279f1ef-2368-447d-b4e0-2a79c0b3cb91.png">












