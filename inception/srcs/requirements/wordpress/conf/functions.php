<?php

require ABSPATH . WPINC . '/option.php';

function fb_wp_insert_user() {
	$user_data = array(
	'ID' => '',
	'user_pass' => wp_generate_password(),
	'user_login' => 'dummy',
	'user_nicename' => 'Dummy',
	'user_url' => '',
	'user_email' => 'dummy@42.fr',
	'display_name' => 'Dummy',
	'nickname' => 'dummy',
	'first_name' => 'Dummy',
	'user_registered' => '2010-05-15 05:55:55',
	'role' => get_option('default_role')
	);
	$user_id = wp_insert_user( $user_data );
}
add_action( 'admin_init', 'fb_wp_insert_user' );

/*
	Rest of file removed to improve clarity, refer to the original functions.php file
*/
