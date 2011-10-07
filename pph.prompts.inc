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

$pph_prompts['p_introduction']['en']['text'] = "Are you a nanny, housekeeper, or elderly care-giver wanting to know more about your rights? Or, are you the parent of a beautiful little one who you hire a nanny to help look after? And do you want to find out how to comply with the law so your wonderful nanny is treated right?  You have come to the right place! ";
$pph_prompts['p_introduction']['es']['text'] = "Spanish version of the introduction";

$pph_prompts['p_options_menu']['en']['text'] = 
"Main menu. To repeat the introduction, press 1. To hear the definition of a domestic worker, press 2.  To hear about minimum wages, press 3. To hear about overtime wages, press 4. To hear about days of rest, press 5. To hear about taxes and being paid off the books, press 6. To hear about wage deductions, press 7. To hear about unemployment insurance, press 8. To record your own story, press 9. To be connected to Domestic Workers United, press the star key. To hang up, press the pound key. ";
$pph_prompts['p_options_menu']['es']['text'] = 'Spanish version of the menu. ';


// Prompts associated with pph_play_announcement_script

