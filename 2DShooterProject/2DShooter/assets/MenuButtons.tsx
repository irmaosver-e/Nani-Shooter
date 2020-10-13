<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="MenuButton" tilewidth="192" tileheight="64" spacing="2" margin="2" tilecount="12" columns="2">
 <image source="MenuButtons.png" width="390" height="398"/>
 <tile id="0" type="playbutton">
  <properties>
   <property name="VsCollision" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="12" y="12" width="168" height="40"/>
  </objectgroup>
  <animation>
   <frame tileid="2" duration="400"/>
   <frame tileid="0" duration="400"/>
  </animation>
 </tile>
 <tile id="1" type="exitbutton">
  <properties>
   <property name="VsCollision" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="12" y="12" width="168" height="40"/>
  </objectgroup>
  <animation>
   <frame tileid="3" duration="400"/>
   <frame tileid="1" duration="400"/>
  </animation>
 </tile>
 <tile id="4" type="resumeButton">
  <properties>
   <property name="VsCollision" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="2" name="collisionBox" x="11.6667" y="12" width="168" height="40"/>
  </objectgroup>
  <animation>
   <frame tileid="6" duration="400"/>
   <frame tileid="4" duration="400"/>
  </animation>
 </tile>
 <tile id="5" type="menuButton">
  <properties>
   <property name="VsCollision" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="11.5" y="12.5" width="168" height="40"/>
  </objectgroup>
  <animation>
   <frame tileid="7" duration="400"/>
   <frame tileid="5" duration="400"/>
  </animation>
 </tile>
 <tile id="9" type="restartButton">
  <properties>
   <property name="VsCollision" value="mousepointer"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="collisionBox" x="12" y="12" width="168" height="40"/>
  </objectgroup>
  <animation>
   <frame tileid="9" duration="400"/>
   <frame tileid="11" duration="400"/>
  </animation>
 </tile>
</tileset>
