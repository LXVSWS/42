<?php

define( 'DB_NAME', 'wordpress' );

define( 'DB_USER', 'lxv' );

define( 'DB_PASSWORD', 'password' );

define( 'DB_HOST', 'mariadb:3306' );

define( 'DB_CHARSET', 'utf8' );

define( 'DB_COLLATE', '' );

define('AUTH_KEY',         'CIcmuHuAPRyxQeN=+s)NuvpOk SR$Xt&-3T+~#a|o-c0Qs|d1#[:H$X&U{G-T&W&');
define('SECURE_AUTH_KEY',  '-Tm~}fbp#NMTBN3;y@:u-7Vntzkc>|{P[zTTn}Oa3vLXq)D-m=%=wGE|yW$EIFX0');
define('LOGGED_IN_KEY',    '.6(DCx%b!SBmT/4|` %|rfJdu+,hxSLZjW8*Vg$j=6`}sAVq{waTt<{-l$[_YGV3');
define('NONCE_KEY',        '}kIQxI$j_-_^&-tVlN#h>ac~-^n6Jq~ZeHY}z7}H:tE_{5SXK<e71.z}8e9aZP}7');
define('AUTH_SALT',        'Z3a~f*zB_SGxA&O/CTeKe2SNWkP9FfW +Yd<;H?~@K6]LA[&S#5}1[,`7aKdO0Is');
define('SECURE_AUTH_SALT', '*bAca0BTR&+Su1fhlkv;?X3G1%H2>lfZI.2;)ZR?<KV>9-9|S6iV0l*1l5J=lxsu');
define('LOGGED_IN_SALT',   '!>_jg;/Ik&Fm5XR^u/?st1l8SsAv<y+ca4i+iCBk.1at>F-zIT-L+=9WvC&$qW]+');
define('NONCE_SALT',       't.fD#]aOEXo@D8-F9T=,v96X.:$QpO|ZO@P]tNKd+p@]dwvW|/>h}[sp1E=y+~?J');

$table_prefix = 'wp_';

define( 'WP_DEBUG', true );

if ( ! defined( 'ABSPATH' ) )
  define( 'ABSPATH', dirname( __FILE__ ) . '/' );

require_once( ABSPATH . 'wp-settings.php' );
