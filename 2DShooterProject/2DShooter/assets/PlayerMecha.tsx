<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.3.5" name="PlayerMecha" tilewidth="64" tileheight="64" spacing="2" margin="2" tilecount="6" columns="3">
 <image source="PlayerMecha.png" width="202" height="136"/>
 <tile id="0" type="playermecha">
  <objectgroup draworder="index" id="2">
   <object id="1" name="colisionBox" x="14" y="9" width="20" height="35"/>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="300"/>
   <frame tileid="1" duration="300"/>
   <frame tileid="2" duration="300"/>
   <frame tileid="3" duration="300"/>
   <frame tileid="4" duration="300"/>
   <frame tileid="5" duration="300"/>
  </animation>
 </tile>
</tileset>