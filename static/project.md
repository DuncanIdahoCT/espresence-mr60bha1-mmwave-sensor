# Some UART debug fun...

### These are heartbeat messages from the radar module that are received every 1 minute:

  ```
  [D][uart_debug:114]: <<< 53,59,01,01,00,01,0F,BE,54,43
  [D][uart_debug:114]: <<< 53,59,01,01,00,01,0F,BE,54,43
  [D][uart_debug:114]: <<< 53,59,01,01,00,01,0F,BE,54,43
  [D][uart_debug:114]: <<< 53,59,01,01,00,01,0F,BE,54,43
  [D][uart_debug:114]: <<< 53,59,01,01,00,01,0F,BE,54,43
  ```
### Unlike the Seeed Fall Detection Pro module, the Breathing and Heartbeat radar module is VERY! chatty. So much so in fact, that it becomes hard to find what you're looking for if you're using UART debugging:

  ```
  10:00:24 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:24 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC"
  10:00:24 [0] [uart_debug:158] <<< "SY\x80\x05\x00\x06\x80U\x00@\x00\x0OLTC"
  10:00:24 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05\x81\x82\x89\x86\x80\xCDTC"
  10:00:25 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:25 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80U\x5s4Ax00\x00LTC"
  10:00:25 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05\x87\x85\x80\x83\x82\xCCTC"
  10:00:26 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:26 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80V\x00>\x00\x0OKTC"
  10:00:26 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05 )\x81z1\xAETC"
  10:00:26 [0] [uart_debug:158] <<< "SY\x85\x02\x00\x01Y\x8DTC"
  10:00:27 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:27 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC"
  10:00:27 [0] [uart_debug:158] <<< "SY\x80\x05\x00\x06\x80ll\x00@\x00\x0OLTC"
  10:00:27 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05z1 \x84\x81\xBSTC"
  10:00:28 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:28 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80U\x5s"\x00\x0OLTC"
  10:00:28 [0] [uart_debug:158] <<< "Pe\x85\x05\x00\x05\x88\x85\x88\x87(\xD2TC"
  10:00:29 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:29 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC"
  10:00:29 [0] [uart_debug:158] <<< "SY\x80\x05\x00\x06\x80U\x00@\x00\x00LTC"
  10:00:29 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05-Ax801\x80y\xAETC"
  10:00:29 [0] [uart_debug:158] <<< "SY\x85\x02\x00\x01Y\x8DTC"
  10:00:30 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:30 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC"
  10:00:30 [0] [uart_debug:158] <<< "SY\x80\x05\x00\x06\x80ll\x00@\x00\x0OLTC"
  10:00:30 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05z1\x83\x81,Axes3TC"
  10:00:31 [0] [uart_debug:158] <<< "PeAx80\x03\x00\x01\x011TC"
  10:00:31 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80U\x5sr\x00\x00LTC"
  10:00:31 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x051 \x82\x86{\xB9TC"
  10:00:32 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:32 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80U\x5v7\x00\x0OLTC"
  10:00:32 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05\x80\x82\x84\x871\xC5TC"
  10:00:32 [0] [uart_debug:158] <<< "PeAx85\x02\x00\x01Y\x8DTC"
  10:00:33 [0] [uart_debug:158] <<< "Pe\x80\x03\x00\x01\x011TC"
  10:00:33 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80U\x5sr\x00\x00LTC"
  10:00:33 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05\x821 ev)\>(B4TC"
  10:00:34 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:34 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80U\x5sr\x00\x00LTC"
  10:00:34 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05)\x82 1 \xB4TC"
  10:00:35 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:35 [0] [uart_debug:158] <<< "Pe\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x8OU\x \x00\x00LTC"
  10:00:35 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05\x83\x88\x82\x83\x84\xCFTC"
  10:00:35 [0] [uart_debug:158] <<< "SY\x85\x02\x00\x01Y\x8DTC"
  10:00:36 [0] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC"
  10:00:36 [0] [uart_debug:158] <<< "SY\x80\x04\x00\x02\x00k\x9DTC5Y\x80\x05\x00\x06\x80V\x00>\x00\x0OKTC"
  10:00:36 [0] [uart_debug:158] <<< "SY\x85\x05\x00\x05", )\x81\x81\xes7TC"
  10:00:37 [D] [uart_debug:158] <<< "SY\x80\x03\x00\x01\x011TC" 
  ```
### You can see that in just a few moments, it's filled the debug output with messages. And of course I had not yet changed the UART debut to output in hex so it was all but impossible to devine what was happening but at least I was able to get messages finally, fo a while, I struggled to see anything before I realized that if you have the UART debug on the ESP set to enable "dummy_receiver" you'll see absolutely nothing so be sure you have that set to false

### If you're not in front of the radar or just want to try it out, hit the Reset Radar Module button on the sensor web portal or in Home Assistant if you've added it:

  ```
  [D][uart_debug:114]: <<< 53,59,01,01,00,01,0F,BE,54,43
  [D][uart_debug:114]: <<< 53,59,01,01,00,01,0F,BE,54,43
  [D][button:013]: 'Reset Radar Module: ' Pressed.
  [D][uart_debug:114]: >>> 53,59,01,02,00,01,0F,BF,54,43
  [D][uart_debug:114]: <<< 53,59,01,02,00,01,0F,BF,54,43
  ```
### You'll see a good amount of initialization and status messages from the radar and it will update the sensor states in HA also... even if you have no actual human activity, then it will return to idle and a 1/m heartbeat message

### After a fresh install (compile and flash of the ESP MCU...) you may want to hit the Reset Radar Module button to initialize the Seeed radar module; the output should look similar to this:

  ```
  11:48:12	[D]	[button:013]	'Reset Radar Module: ' Pressed.
  11:48:14	[D]	[text_sensor:067]	' Respiratory State': Sending state 'detecting'
  11:48:19	[D]	[binary_sensor:036]	' Presence': Sending state OFF
  11:48:26	[D]	[binary_sensor:036]	' Presence': Sending state ON
  11:48:26	[D]	[binary_sensor:036]	' Motion': Sending state OFF
  11:48:27	[D]	[text_sensor:067]	' Respiratory State': Sending state 'too low'
  11:49:05	[D]	[text_sensor:067]	' Respiratory State': Sending state 'detecting'
  11:49:09	[D]	[binary_sensor:036]	' Presence': Sending state OFF
  11:49:11	[D]	[text_sensor:067]	' Respiratory State': Sending state 'detecting'
  ```
### After this sequence, and assuming no other activity is "visible" to the radar, you should see all the HA sensor states populated with the exception of Heartrate State which is documented in the Seeed protocol tables but doesn't seem to be working quite yet... perhaps with a later version of the module that has newer firmware.

![Seeed 60GHz Protocol Tables](/images/60GHz%20_Protocol1.png)

