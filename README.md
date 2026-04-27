# **Windows Bluetooth Volume Fix (Because Microsoft won't)**



I don't know if Microsoft intentionally ignores this or if they just stopped caring about Windows altogether.



Every time you connect a Bluetooth audio device—speakers, earbuds, neckbands, you name it—Windows forces the volume to 100%. If you're wearing earbuds, your ears get blasted. If you’re using speakers, you’re basically guaranteed to annoy everyone in the house or your neighbors the second you play anything.



Android figured this out years ago. Windows should have a simple, built-in setting to cap the initial connection volume, but instead, we’re stuck manually fighting the volume slider every single time. It’s annoying, especially if you rely on Bluetooth for daily use.



### **The Fix I Came Up With**



I did some browsing and figured out there is no direct Windows API call to modify volume programmatically but there's a third party app named AutoHotkey that offers it for free. I made a simple one file program right here with C++ using that advantage to lower volume automatically.



**How it works:** This C++ implementation detects when your device connects and instantly drops the volume to a safe level (default is 20%). This makes the transition smooth and hassle free.



**Safety:** It restores your previous volume settings upon disconnect.



**Customization:** I’ve hardcoded this for my AirPods, so you'll need to tweak the code to target your specific device.



**Usage:** Keep it running in the background and stop worrying about blowing out your eardrums.





### **A Quick Heads-Up**



**AutoHotkey Dependency:** Ensure you have AutoHotkey installed, as the C++ logic relies on it to bypass Windows' lack of a direct volume API.



**Alpha Build:** This is a test implementation. It works for me, but it's not "plug-and-play" for everyone yet.



**Hardcoded Values:** Right now, it's set specifically for my AirPods. You must modify the device ID/name in the source for it to work with your hardware.







### **License**

I’m sticking this under the **MIT License**. It’s lightweight and keeps the code open for anyone to tweak, as long as you keep the original copyright notice.
