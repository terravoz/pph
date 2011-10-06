<?php

/**
 * Constant definitions
 */

define('PCN_AUDIO_URL', 'http://whatsupserver.media.mit.edu/public/pcn/prompts/');

/**
 * Global variables
 */

global $pcn_prompts;

/**
 * Function definitions
 */

function v($index, $language='en') {
  global $pcn_prompts;
if(!$pcn_prompts[$index]) { watchdog('pcn', "missing $index"); }
  $file_name = $pcn_prompts[$index][$language]['file_name'];
  if($file_name) {
    $rc = PCN_AUDIO_URL . $file_name;
  }
  else {
    $rc = $pcn_prompts[$index][$language]['text'];
  }
  return $rc;
}

function pcn_get_missing_prompt_recordings_list($language='en') {
  global $pcn_prompts;
  foreach($pcn_prompts as $prompt) {
    if(!$prompt[$language]['file_name']) {
      $list[] = $prompt[$language]['text'];
    } 
  }
  return $list;
}


/**
 * Prompts
 */

// Messages that appear in more than one script

$pcn_prompts['p_invalid_msg']['en']['text'] = 'Invalid option selected';
//$pcn_prompts['p_invalid_msg']['en']['file_name'] = 'p_invalid_msg.mp3';


// Prompts associated with the pcn_welcome script

$pcn_prompts['p_greetings']['en']['text'] = 'Welcome to the Parent Connectors Hotline. ';
$pcn_prompts['p_greetings']['en']['file_name'] = 'welcome.mp3';

//$pcn_prompts['p_language_selection_menu']['en']['text'] = "For English, press 1. For Spanish, press 2. For Portuguese, press 3. For Creole, press 4. ";
$es_msg_url = PCN_AUDIO_URL . 'es_press_2.mp3';
$pt_msg_url = PCN_AUDIO_URL . 'pt_press_3.mp3';
$ht_msg_url = PCN_AUDIO_URL . 'ht_press_4.mp3';
$pcn_prompts['p_language_selection_menu']['en']['text'] = "For English, press 1. $es_msg_url $pt_msg_url $ht_msg_url ";
//$pcn_prompts['p_language_selection_menu']['en']['file_name'] = "p_language_selection_menu.mp3";

$pcn_prompts['p_thank_you']['en']['text'] = 'Thank you for calling the Parent Connectors hotline. ';
$pcn_prompts['p_thank_you']['es']['text'] = '(In Spanish) Thank you for calling the Parent Connectors hotline. ';
$pcn_prompts['p_thank_you']['pt']['text'] = '(In Portuguese) Thank you for calling the Parent Connectors hotline. ';
$pcn_prompts['p_thank_you']['ht']['text'] = '(In Creole) Thank you for calling the Parent Connectors hotline. ';


// Prompts associated with pcn_options_script

$pcn_prompts['p_options_menu']['en']['text'] = 'To listen to the latest announcement, press 1. To record a message or a question to the Parent Connectors, press the star key. ';
$pcn_prompts['p_options_menu']['es']['text'] = '(In Spanish) To listen to the latest announcement, press 1. To record a message or a question to the Parent Connectors, press the star key. ';
$pcn_prompts['p_options_menu']['pt']['text'] = '(In Portuguese) To listen to the latest announcement, press 1. To record a message or a question to the Parent Connectors, press the star key. ';
$pcn_prompts['p_options_menu']['ht']['text'] = '(In Creole) To listen to the latest announcement, press 1. To record a message or a question to the Parent Connectors, press the star key. ';


// Prompts associated with pcn_play_announcement_script

