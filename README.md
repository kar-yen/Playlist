# Randomised playlist: “DJ for an hour”

A program that sorts the input playlist alphabetically and produces a randomised set of songs from a longer 
list entered as input.

## 1 &nbsp;Input
The program takes its input from a file specified as an argument to the program. 
* If the file does not exists or is not readable, the program prints out an error message to this effect.
* If no file is specifed, the program searches in the current directory for a file called artistes+songs.txt. 
* If no such file exists, the program prints a message “No file found.” and then prompts the user to enter the 
artistes and songs information from the keyboard according to the specified format. <br />
The format of the file is as follows:
```
Artiste name
Song title***Song duration
Song title***Song duration
...
Song title***Song duration
<blank line>
Artiste name
Song title***Song duration
Song title***Song duration
...
Song title***Song duration
<blank line>
...
```
Each song title comprises alphanumeric characters (letters, numbers and symbols) but does not contain the 
sub-string “\*\*\*”. <br />
“Song duration” is in the form [m]m:ss, where [m]m denotes a one- or two-digit number of minutes and ss
denotes a two-digit number of seconds.

## 2 &nbsp;Sort Artistes And Songs
The program then sort the input by artiste name and then by song title and print it out in the following format:
```
Sorted list of artistes and songs
Artiste name
o Song title***Song duration
o Song title***Song duration
...
o Song title***Song duration
<blank line>
Artiste name
o Song title***Song duration
o Song title***Song duration
...
o Song title***Song duration
```

## 3 &nbsp;Produce Randomised Playlist
The program should then generate a random playlist of the songs given as input, according to the following constraints:
* An artiste cannot have more than two songs in a row (so no “triple play”, as the radio DJs might say);
* An artiste cannot have more than three songs in total in the playlist;
* A song cannot appear twice in the playlist;
* The total playlist length should be as close as possible to one hour. Specifically, the last song must start on or
before 59:59. 

The randomised playlist and the total time should be printed out in the following format: <br />
```
Randomised playlist
Artiste name: "Song title" (Song duration)
Artiste name: "Song title" (Song duration)
...
Artiste name: "Song title" (Song duration)
Total duration: <Total duration>.
```

## 3 &nbsp;Example
### 3.1 &nbsp;Input File
```
The National
Fireproof***2:58
Hard to Find***4:13
England***5:40
Son***5:20
Light Years***3:32
Lean***4:31
The System Only Dreams in Total Darkness***3:56

Arcade Fire
Rebellion (Lies)***5:10
Wake Up***5:39
Cold Wind***3:12
Neighborhood #1 (Tunnels)***4:48
Neighborhood #3 (Power Out)***5:12

The War on Drugs
Under the Pressure***8:51
Red Eyes***4:58

Sufjan Stevens
Go! Chicago! Go! Yeah!***6:04
Chicago [To String Remix]***5:32
Carrie & Lowell***3:14
John My Beloved***5:03

London Grammar
Wasting My Young Years***3:24
Strong [Hackman remix]***5:13

Jos Gonzlez
Heartbeats***2:40

Bon Iver
29 #Strafford APTS***4:05
00000 Million***3:53
re: Stacks***6:40

Future Islands
Tin Man***3:14
Seasons (Waiting on You)***3:46
Grease***4:35
Spirit***4:22

Public Service Broadcasting
They Gave Me A Lamp***3:56
The Other Side***6:20
Go!***4:13
```

### 3.2 &nbsp;Sorted Playlist
```
Sorted list of artistes and songs
Arcade Fire
o Cold Wind***3:12
o Rebellion (Lies)***5:10
o Neighborhood #1 (Tunnels)***4:48
o Neighborhood #3 (Power Out)***5:12
o Wake Up***5:39

Bon Iver
o 00000 Million***3:53
o 29 #Strafford APTS***4:05
o re: Stacks***6:40

Future Islands
o Grease***4:35
o Seasons (Waiting on You)***3:46
o Spirit***4:22
o Tin Man***3:14

Jos Gonzlez
o Heartbeats***2:40

London Grammar
o Strong [Hackman remix]***5:13
o Wasting My Young Years***3:24

Public Service Broadcasting
o Go!***4:13
o The Other Side***6:20
o They Gave Me A Lamp***3:56

Sufjan Stevens
o Carrie & Lowell***3:14
o Chicago [To String Remix]***5:32
o Go! Chicago! Go! Yeah!***6:04
o John My Beloved***5:03

The National
o England***5:40
o Fireproof***2:58
o Hard to Find***4:13
o Lean***4:31
o Light Years***3:32
o Son***5:20
o The System Only Dreams in Total Darkness***3:56

The War on Drugs
o Red Eyes***4:58
o Under the Pressure***8:51
```

### 3.3 &nbsp;Randomised Playlist
```
Randomised playlist
Public Service Broadcasting: "They Gave Me A Lamp" (3:56)
The War on Drugs: "Under the Pressure" (8:51)
Future Islands: "Spirit" (4:22)
Arcade Fire: "Cold Wind" (3:12)
The National: "England" (5:40)
Bon Iver: "re: Stacks" (6:40)
Sufjan Stevens: "Chicago [To String Remix]" (5:32)
Jos Gonzlez: "Heartbeats" (2:40)
Public Service Broadcasting: "The Other Side" (6:20)
Public Service Broadcasting: "Go!" (4:13)
Arcade Fire: "Rebellion (Lies)" (5:10)
London Grammar: "Wasting My Young Years" (3:24)
Total duration: 60:00.
```
