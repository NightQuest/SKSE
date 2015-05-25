Skyrim Script Extender v1.7.3
by Ian Patterson and Stephen Abel (ianpatt and behippo)
Thanks to: Paul Connelly (scruggsywuggsy the ferret), gibbed, Purple Lunchbox, snakster

The Skyrim Script Extender, or SKSE for short, is a modder's resource that expands the scripting capabilities of Skyrim. It does so without modifying the executable files on disk, so there are no permanent side effects.

Compatibility:

SKSE will support the latest version of Skyrim available on Steam, and _only_ this version (currently 1.9.32 with any combination of numbers after that). When a new version is released, we will update as soon as possible; please be patient. The editor does not currently need modification, however a custom set of .pex/psc files must be installed.

[ Installation ]

1. Copy the .dll and .exe files to your Skyrim directory. This is usually in your Program Files folder under Steam\SteamApps\common\skyrim\. If you see files named TESV and SkyrimLauncher, this is the correct folder. Do not copy these files to the Data folder as with a normal mod. The "src" folder is only useful for programmers, most users can ignore it.

2. Copy the .pex files in Data\Scripts\ into the Data\Scripts\ folder of your installation. The .pex files are needed by all users of SKSE. 

3. If you create mods, copy the .psc files in Data\Scripts\Source\ into the Data\Scripts\Source\ folder of your installation. The .psc files are only needed if you have the CreationKit installed and intend to create or compile Papyrus scripts.

4. Steam will automatically load SKSE if found. If you want more control over the launch process, you can keep using skse_loader.exe.

[ Suggestions for Modders ]

If your mod requires SKSE, please provide a link to the main SKSE website <http://skse.silverlock.org/> instead of packaging it with your mod install. Future versions of SKSE will be backwards compatibile, so including a potentially old version can cause confusion and/or break other mods which require newer versions.

[ Troubleshooting / FAQ ]

* Crashes or strange behavior:
 - Let us know how you made it crash, and we'll look into fixing it.

* 360 or PS3 version?
 - No.

* My virus scanner complains about skse_loader!
 - It is not a virus. To extend Skyrim and the editor, we use a technique called DLL injection to load our code. Since this technique can also be used by viruses, some badly-written virus scanners assume that any program doing it is a virus. Adding an exception to your scanner's rules may be necessary.

* I've followed the directions, but Skyrim still seems to launch without SKSE!
- Try running skse_loader.exe as an Administrator by right-clicking on skse_loader.exe and selecting "Run As Administrator". This can be enabled as a compatibility option in the program's properties window.
 
* Can I modify and release my own version of SKSE based on the included source code?
 - No; the suggested method for extending SKSE is to write a plugin. If this does not meet your needs, please email the contact addresses listed below.

* How do I write Papyrus scripts using SKSE extensions?
 - If you've properly installed the .psc files from Data\Scripts\Source you can simply use the new functions listed.
 
* How do I know what SKSE functions have been added?
 - Look at the included .psc files in Data\Scripts\Source\. At the bottom of each .psc file is a label that shows the SKSE functions which have been added. Most have comments describing their purpose, if it is not obvious from the name.

* How do I write a plugin for SKSE?
 - See PluginAPI.h for instructions, as well as the example plugin project included with the rest of the source code.

* Can I include SKSE as part of a mod pack/collection or otherwise rehost the files?
 - No. Providing a link to http://skse.silverlock.org/ is the suggested method of distribution. Exceptions may be given under applicable circumstances; contact us at the email addresses below. This means that if you see this file available for download anywhere other than http://skse.silverlock.org, that service is violating copyright. I don't like having to explicitly spell this out, but my hand has been forced.

* Does SKSE work with a 4GB loader?
 - 4GB loaders are no longer needed.

* Do I need to keep old SKSE DLLs around for backwards compatibility?
 - No, they are only needed if you want to run old versions of the runtime with the last version of SKSE released for that version. Feel free to delete any skse_*.dll files that are not included with the main archive.

* Where did the log files go?
 - To support users on machines that don't have write access to the Program Files folder, they have been moved to the <My Documents>\My Games\Skyrim\SKSE\ folder.

* Where is the skse.ini file?
 - SKSE does not include one by default. Create an empty text file in <skyrim root>\Data\SKSE\ named skse.ini. Create the SKSE folder if it doesn't already exist.

* How do I uninstall SKSE?
 - Delete the .dll and .exe files starting with skse_ from your Skyrim folder.

[ Contact the SKSE Team ]

Before contacting us, make sure that your game launches properly without SKSE first. If SKSE doesn't appear to be working, follow the steps in the FAQ first, then send us skse.log, skse_loader.log, and skse_steam_loader.log as attachments. These files may be found in <My Documents>\My Games\Skyrim\SKSE\.

### MAKE SURE TO INCLUDE YOUR LOG FILES AS ATTACHMENTS ###
We cannot help you solve load order problems.

Entire Team
Send email to team [at] skse [dot] silverlock [dot] org

Ian (ianpatt)
Send email to ianpatt+skse [at] gmail [dot] com

Stephen (behippo)
Send email to gamer [at] silverlock [dot] org

[ Standard Disclaimer ]

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
