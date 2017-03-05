# Mini-Project in Disk-Management

This project aims to illustrate the way files are stored in a disk.<br />
The main logic and operation are written in C++, and the UI in C# using WPF. <br />
We used <a href="https://msdn.microsoft.com/en-us/library/system.runtime.interopservices.marshal(v=vs.110).aspx">Marshal</a> in order to work with the unmanaged code in our WPF UI application.<br />

To compile the project:
  - Make sure you have MS Visual Studio 2015 or higher with all the C++ libraries installed.
  - Make sure that all the nuget packages are installed with the latest version
  - Build the projects exactly in this order:
      - FMS5776_2075_3798
      - FMS_DLL
      - FMS_Adapter
      - FMS_GUI
  - The reason for that is the fact that we couldn't find a way to force pre-compilation of the native code before the C# code.

There is still no input validation in the UI, so make sure you are typing the right values.

Screenshots:

<a href='https://postimg.org/image/sdz5o4lpb/' target='_blank'><img src='https://s19.postimg.org/3kplnh2oz/image.png' border='0' alt="1" width="49%"/></a> 
<a href='https://postimg.org/image/9a5u7s8v3/' target='_blank'><img src='https://s19.postimg.org/ngll30jqb/image.png' border='0' alt="2"
width="49%"/></a><br/><br/>
<a href='https://postimg.org/image/x2f5jbavz/' target='_blank'><img src='https://s19.postimg.org/pz7a3p5gj/image.png' border='0' alt="3"
width="49%"/></a> 
<a href='https://postimg.org/image/c6sv82eov/' target='_blank'><img src='https://s19.postimg.org/5gcdymrj7/image.png' border='0' alt="4"
width="49%"/></a><br/><br/>
<a href='https://postimg.org/image/iyjaax3of/' target='_blank'><img src='https://s19.postimg.org/svub3zbab/image.png' border='0' alt="5"
width="49%"/></a> 
<a href='https://postimg.org/image/6xxua6w9r/' target='_blank'><img src='https://s19.postimg.org/bwlcoq02r/image.png' border='0' alt="6"
width="49%"/></a><br/><br/>
<a href='https://postimg.org/image/dpo9d1l9b/' target='_blank'><img src='https://s19.postimg.org/s8veegeeb/image.png' border='0' alt="7"
width="49%"/></a> 
<a href='https://postimg.org/image/xybmyrkkf/' target='_blank'><img src='https://s19.postimg.org/gl1cjwp9f/image.png' border='0' alt="8"
width="49%"/></a><br/><br/>
<a href='https://postimg.org/image/a8m7a2m73/' target='_blank'><img src='https://s19.postimg.org/r953iqz8j/image.png' border='0' alt="9"
width="49%"/></a> 
<br />

<!--https://postimg.org/gallery/xt625lds/4b3c576d/-->
