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

$pph_prompts['p_greetings']['en']['text'] = 'Welcome to the Domestic Workers United Hotline. ';

$pph_prompts['p_language_selection_menu']['en']['text'] = "For English, press 1. For Spanish, press 2. ";

$pph_prompts['p_thank_you']['en']['text'] = 'Thank you for calling the DWU hotline. ';
$pph_prompts['p_thank_you']['es']['text'] = '(In Spanish) Thank you for calling the DWU hotline. ';


// Prompts associated with pph_main_menu_script

$pph_prompts['p_introduction']['en']['text'] = "Are you a nanny, housekeeper, or elderly care-giver wanting to know more about your rights? Or, are you the parent of a beautiful little one who you hire a nanny to help look after? And do you want to find out how to comply with the law so your wonderful nanny is treated right?  You have come to the right place! ";
$pph_prompts['p_introduction']['es']['text'] = "Spanish version of the introduction";

$pph_prompts['p_options_menu']['en']['text'] = 
"Main menu. To repeat the introduction, press 1. To hear the definition of a domestic worker, press 2.  To hear about minimum wages, press 3. To hear about overtime wages, press 4. To hear about days of rest, press 5. To hear about taxes and being paid off the books, press 6. To hear about wage deductions, press 7. To hear about unemployment insurance, press 8. To record your own story, press 9. To be connected to Domestic Workers United, press the star key. To hang up, press the pound key. ";
$pph_prompts['p_options_menu']['es']['text'] = 'Spanish version of the main menu. ';


// Prompts associated with pph_play_story_script

$pph_prompts['p_definition']['en']['text'] = "Here the system will play an episode about definition of a domestic worker. ";

$pph_prompts['p_minimum_wages']['en']['text'] = "Here the system will play an episode about minimum wages. ";

$pph_prompts['p_overtime_wages']['en']['text'] = "Here the system will play an episode about overtime wages. ";

$pph_prompts['p_days_of_rest']['en']['text'] = "Here the system will play an episode about days of rest. ";

$pph_prompts['p_taxes']['en']['text'] = "Here the system will play an episode about taxes. ";

$pph_prompts['p_wage_deduction']['en']['text'] = "Here the system will play an episode about wage deduction. ";

$pph_prompts['p_insurance']['en']['text'] = "Here the system will play an episode about insurance. ";

$pph_prompts['p_instructions']['en']['text'] = 'While listening, feel free to press any key to go to the story menu. ';

$pph_prompts['p_playback_menu']['en']['text'] = 'To listen to the story once again, press 1. To go back to the main menu, press the pound key. ';

//-----------------------
//$p_definition[] = new VoipPrompt('Helloooo, Caller! I am Christine Lewis and in this episode of "New Day New Standard," we are going to define exactly what a "domestic worker" is.  Narrator, can ya define that for us, now?', 'woman');
$p_definition[] = new VoipPrompt('Helloooo, Caller! I am Christine Lewis and in this episode of New Day, New Standard, we are going to define exactly what a domestic worker is.  Narrator, can ya define that for us, now?', 'woman');


$p_definition[] = new VoipPrompt('Domestic workers are nannies, housekeepers, and elder caregivers who provide invaluable labor that frees others to work outside the home. In the state of New York, there are over 200 thousand domestic workers. Until now, domestic workers have largely been an invisible workforce in the eyes of the state. However, in November of 2010, the passage of the New York Domestic Worker Bill of Rights expanded labor protection for domestic workers and has raised public awareness of the problems of the industry.', 'man');

$p_definition[] = new VoipPrompt('You are probably wondering what that means for you.', 'woman');

$p_definition[] = new VoipPrompt('If you are a domestic worker, both the Fair Labor Standards ACT and New York Labor Law prohibit an employer from firing or otherwise retaliating against you for exercising your rights under wage and hour laws.', 'man');

$p_definition[] = new VoipPrompt('So if you are a domestic worker, this means you are now covered by a new set of laws, even if you are paid off the books!', 'woman');

$p_definition[] = new VoipPrompt('But remember to keep records of the hours you worked and the wages you were paid!', 'man');

$p_definition[] = new VoipPrompt('Thats right: this is a new day new standard. Its very exciting and you are part of a movement that is paving the path for others. If you are the employer of a domestic worker, this means that you have new responsibilities. Are ya complying?', 'woman');

$pph_prompts['p_definition']['en']['text'] = $p_definition;

