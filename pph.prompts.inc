<?php

/**
 * Constant definitions
 */

define('PPH_AUDIO_URL', 'http://whatsupserver.media.mit.edu/public/pph/prompts/');

/**
 * Global variables
 */

global $pph_prompts;

/**
 * Function definitions
 */

function v($index, $language='en') {
  global $pph_prompts;
if(!$pph_prompts[$index]) { watchdog('pph', "missing $index"); }
  $file_name = $pph_prompts[$index][$language]['file_name'];
  if($file_name) {
    $rc = PPH_AUDIO_URL . $file_name;
  }
  else {
    $rc = $pph_prompts[$index][$language]['text'];
  }
  return $rc;
}

function pph_get_missing_prompt_recordings_list($language='en') {
  global $pph_prompts;
  foreach($pph_prompts as $prompt) {
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

$pph_prompts['p_invalid_msg']['en']['text'] = 'Invalid option selected';
//$pph_prompts['p_invalid_msg']['en']['file_name'] = 'p_invalid_msg.mp3';


// Prompts associated with the pph_welcome script

$pph_prompts['p_greetings']['en']['text'] = 'Welcome to the DWU Hotline. ';

$pph_prompts['p_language_selection_menu']['en']['text'] = "For English, press 1. For Spanish, press 2. ";

$pph_prompts['p_thank_you']['en']['text'] = 'Thank you for calling the DWU hotline. ';
$pph_prompts['p_thank_you']['es']['text'] = '(In Spanish) Thank you for calling the DWU hotline. ';


// Prompts associated with pph_main_menu_script

$pph_prompts['p_introduction']['en']['text'] = 'This system does this, but it also does that. ';
$pph_prompts['p_options_menu']['en']['text'] = 'To listen to the latest announcement, press 1. To record a message or a question to the Parent Connectors, press the star key. ';
$pph_prompts['p_options_menu']['es']['text'] = '(In Spanish) To listen to the latest announcement, press 1. To record a message or a question to the Parent Connectors, press the star key. ';


// Prompts associated with pph_play_announcement_script

