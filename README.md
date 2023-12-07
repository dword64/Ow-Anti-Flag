

# Anti-Flag for Overwatch

**Anti-Flag** is a simply Console Application written in modern C++. It prevents Chainban's by clearing common Directories and Registry Keys, which Blizzard and Cheat Developers use to *Flag* your Device if you either were a Bad Boy >:( or downloaded malware disguised as Overwatch Cheats.

## Why ?

As Blizzard keeps getting more aggressive with Bans, we have decide to make this Public in an effort to stop them from blindly flailing a shotgun around and taking out every Account that may just show the *slightest* signs of being either Cheated on or being Botted by a Levelling Script. 

## Please Note !

After reverse engineering parts of Overwatch (*including the "Device-Identification"-Function*), these are the things that affect [Blizzards Device Fingerprints](https://github.com/Avalon-Group/Blizzard-Device-Identification-Explained):
- [ACP](https://docs.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-getacp)
- [User Default Language ID](https://docs.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-getuserdefaultlangid)
- [System Default Language ID](https://docs.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-getsystemdefaultlangid)
- [Computer Name](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getcomputernamew) (*Anti-Flag changes this*)
- [Username](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getusernamew)
- [Timezone Information](https://docs.microsoft.com/en-us/windows/win32/api/timezoneapi/nf-timezoneapi-gettimezoneinformation)
- [CPU ID](https://docs.microsoft.com/en-us/cpp/intrinsics/cpuid-cpuidex?view=msvc-160)
- [RTL Version](https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-rtlgetversion)

Generally you are fine with just using Anti-Flag, as Blizzard generates one large "string" by chaining all the above listed calls together, so even the smallest change (*in our case the Device Name*) **will** change this Fingerprint/Device-Hash.
 


## How to Use ?

Just run it **as Administrator**, that's it really. 

## How to Build ?

Simple, **Clone the Repository** and **open the Solution**, *you may need some SDK's as we are using C++ Version 17*.
To actually *Build* the Project all you have to do is select the **Release Configuration** and... well... *build it*.

## Credits

- **Jayy** from Kaizen BST for originally coming up with the Idea. 
- **Dword and Sixmax** for doing more research on the topic and adding more stuff to the original Idea.

## License

We have decided to put this Project under **AGPL-3.0**!
https://choosealicense.com/licenses/agpl-3.0/

### Other Versions
[Anti-Flag C# Version](https://github.com/AVISIX/Anti-Flag)
