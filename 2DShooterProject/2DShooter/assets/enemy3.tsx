<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.4" tiledversion="1.4.2" name="enemy3" tilewidth="32" tileheight="32" spacing="2" margin="2" tilecount="3" columns="3">
 <image source="enemy3.png" width="104" height="35"/>
 <tile id="0" type="enemyTest3">
  <properties>
   <property name="VsCollision" value="bulletSmall"/>
  </properties>
  <objectgroup draworder="index" id="2">
   <object id="1" name="colisionBox" x="4.6591" y="4.95455" width="24.1818" height="21.8409"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="400"/>
   <frame tileid="1" duration="400"/>
   <frame tileid="2" duration="400"/>
  </animation>
 </tile>
</tileset>