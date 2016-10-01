# Wear-emin

‘Wear-emin’ is a digital music synthesizer that is controlled through gestures designed to replicate a traditional Theremin. 

The aim of the device is to apply a no-touch interaction principle to a wearable, digital, musical device. The ‘Wear-emin’ is paired with a web application that provides the user with an interface to help the user to use the device and become more proficient in using it.

This was the final project for the Mobile HCI class (HCIN722) at Rochester Institute of Technology.

![wear-emin](https://raw.githubusercontent.com/chandan-mahapatra/wearemin/master/wearemin.png)

## Video

<iframe width="560" height="315" src="https://www.youtube.com/embed/BEvPSjRtU2k" frameborder="0" allowfullscreen></iframe>


## Working

First, put the wear-emin on the left hand, and then turn the device on, and activate the associated application. Using the Wear-emin is as simple as flexing one’s hand up and down at the wrist to navigate the musical scale. 

Upward wrist motion produces higher pitches with downward motion creating lower ones. Then, to increase play precision and to control the beat of the music, obstructing the sight of the proximity sensor with one’s thumb tells the Wear-emin to play a note at the pitch selected by the user’s hand position. Quick motions of the thumb across the sensor will produce but one note while leaving the thumb in place will place a continuous sound.

The web application is used provide the user with an interface that make understand and use the device. 
The web application contains an array of 8 rounded rectangles which are blank and get filled if the particular note is selected by the user. 
We took the melody of “Happy Birthday” for the purpose of this study. The application displays the individual notes for the song which can be used as guidance as the user plays the same

![Web Application](https://raw.githubusercontent.com/chandan-mahapatra/wearemin/master/web-application.png)

#### Credit

https://docs.particle.io/reference/firmware/photon

https://community.particle.io/t/tutorial-getting-started-with-spark-publish/3422

https://github.com/twbs/bootstrap

https://learn.sparkfun.com/tutorials/photon-imu-shield-hookup-guide
