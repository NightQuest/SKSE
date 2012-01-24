Skyrim Script Extender v1.4.3
by Ian Patterson, Stephen Abel and Paul Connelly
(ianpatt, behippo and scruggsywuggsy the ferret)

The Skyrim Script Extender, or SKSE for short, is a modder's resource that expands the scripting capabilities of Skyrim. It does so without modifying the executable files on disk, so there are no permanent side effects.

Compatibility:

SKSE will support the latest version of Skyrim available on Steam, and _only_ this version (currently 1.3.10.0). When a new version is released, we will update as soon as possible; please be patient. No editor has been released yet.

[ Installation ]

1. Copy the .dll and .exe files to your Skyrim directory. This is usually in your Program Files folder under Steam\SteamApps\common\skyrim\. If you see files named TESV and SkyrimLauncher, this is the correct folder. Do not copy these files to the Data folder as with a normal mod. The "src" folder is only useful for programmers, most users can ignore it.

2. Launch the game via running skse_loader.exe.

Scripts written with these new commands must be created via the editor after it is launched via skse_loader. Open a command prompt window, navigate to your Skyrim directory, and type "skse_loader -editor". Alternately you can create a shortcut to skse_loader.exe, open the properties window and add "-editor" to the Target field. The normal editor can open plugins with these extended scripts, but it cannot recompile them and will give errors if you try.

[ Suggestions for Modders ]

If your mod requires SKSE, please provide a link to the main SKSE website <http://skse.silverlock.org/> instead of packaging it with your mod install. Future versions of SKSE will be backwards compatibile, so including a potentially old version can cause confusion and/or break other mods which require newer versions.

When your mod loads, use the command GetSKSERelease to make sure a compatible version of SKSE is installed. This command will return an integer that will be incremented for every release of SKSE, making version checking simple. GetSKSEVersion/Minor/Beta are still available, but those are suggested to be used only to report version numbers to the user.

if GetSKSERelease < 5
   MessageBox "This mod requires a newer version of SKSE."
endif

[ Troubleshooting / FAQ ]

* Crashes or strange behavior:
 - Let us know how you made it crash, and we'll look into fixing it.

* XBox 360 or PS3 version?
 - No.

* My virus scanner complains about skse_loader!
 - It is not a virus. To extend Skyrim and the editor, we use a technique called DLL injection to load our code. Since this technique can also be used by viruses, some badly-written virus scanners assume that any program doing it is a virus. Adding an exception to your scanner's rules may be necessary.

* Can I modify and release my own version of SKSE based on the included source code?
 - No; the suggested method for extending SKSE is to write a plugin. If this does not meet your needs, please email the contact addresses listed below.

* How do I write a plugin for SKSE?
 - See PluginAPI.h for instructions, as well as the example plugin project included with the rest of the source code.

* Can I include SKSE as part of a mod pack/collection or otherwise rehost the files?
 - No. Providing a link to http://skse.silverlock.org/ is the suggested method of distribution. Exceptions may be given under applicable circumstances; contact us at the email addresses below. This means that if you see this file available for download anywhere other than http://skse.silverlock.org, that service is violating copyright. I don't like having to explicitly spell this out, but my hand has been forced.

* Does SKSE work with a 4GB loader?
 - Yes, use http://skyrimnexus.com/downloads/file.php?id=1013.

[ Contact the SKSE Team ]

Before contacting us, make sure that your game launches properly without SKSE first. If SKSE doesn't appear to be working, follow the steps in the FAQ first, then send us skse.log, skse_loader.log, and skse_steam_loader.log as attachments.

Entire Team
Send email to team [at] skse [dot] silverlock [dot] org

Ian (ianpatt)
Send email to ianpatt+skse [at] gmail [dot] com

Stephen (behippo)
Send email to gamer [at] silverlock [dot] org

Paul (scruggsy)
Send email to scruggsyw [at] comcast [dot] net

[ Standard Disclaimer ]

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Thank you MIT license for providing a standard boilerplate legal disclaimer.
