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

$pph_prompts['p_greetings']['en']['text'] = 'Welcome to New Day New Standard, a show about the Domestic Workers Bill of Rights. ';
$pph_prompts['p_greetings']['es']['text'] = '(In Spanish) Welcome to New Day New Standard, a show about the Domestic Workers Bill of Rights. ';

$pph_prompts['p_language_selection_menu']['en']['text'] = "For Spanish, press 1. For English, press 2. ";
$pph_prompts['p_language_selection_menu']['es']['text'] = "Not used. ";

$pph_prompts['p_thank_you']['en']['text'] = "Thank you for calling New Day New Standard. For more information about this show or about Domestic Workers United go to h t t p know your rights n y dot org or call 2 1 2 4 8 1 5 7 4 7. ";
$pph_prompts['p_thank_you']['es']['text'] = "(in Spanish) Thank you for calling New Day New Standard. For more information about this show or about Domestic Workers United go to know your rights n y dot org or call 2 1 2 4 8 1 5 7 4 7. ";


// Prompts associated with pph_main_menu_script

$pph_prompts['p_introduction']['en']['text']
  = "New Day New Standard is an interactive talk show about the new Domestic Workers Bill of Rights. I am Christine. "
  . " And I am Miss Know it All. During this talk show, you get to use your telephone to learn about different parts of the law. "
  . " as well as share your stories and be connected with Domestic Workers United. There is also more info online at w w w dot know your rights n y dot org. ";
$pph_prompts['p_introduction']['es']['text'] = "Spanish version of the introduction";

$pph_prompts['p_options_menu']['en']['text'] = 
"Main menu. To hear exciting episodes about the Domestic Workers Bill of Rights, press 1. To learn more about Domestic Workers United and upcoming meetings, press 2. To report an abuse, press 3. To share a positive story, press 4. To hear about penalties for employers who do not comply with the law, press 5. To hang up press the pound key. "; 
$pph_prompts['p_options_menu']['es']['text'] = 'Spanish version of the main menu. ';

// Prompts associated with the episode directory

$pph_prompts['p_episode_directory']['en']['text'] = 
"Episode directory. To hear about the definition of a domestic worker, press 1. To hear about minimum wages, press 2. To hear about overtime wages, press 3. To hear about paying your taxes, press 4. To hear about wage deductions, press 5. To hear about unemployment insurance, press 6. To hear about immigration issues for domestic workers, trafficking, and modern day slavery, press 7. To go back to the main menu, press the pound key. You can also find copies of contracts, guidelines, and other resources at w w w dot know your rights n y dot org. ";
$pph_prompts['p_episode_directory']['es']['text'] = 'Spanish version of the episode directory. ';


// Prompts associated with pph_play_story_script

$pph_prompts['p_definition']['en']['text'] = "Here the system will play an episode about definition of a domestic worker. ";

$pph_prompts['p_minimum_wages']['en']['text'] = "Here the system will play an episode about minimum wages. ";

$pph_prompts['p_overtime_wages']['en']['text'] = "Here the system will play an episode about overtime wages. ";

$pph_prompts['p_wage_deduction']['en']['text'] = "Here the system will play an episode about wage deduction. ";

$pph_prompts['p_insurance']['en']['text'] = "Here the system will play an episode about insurance. ";

$pph_prompts['p_immigration']['en']['text'] = "Here the system will play an episode about immigration. ";


$pph_prompts['p_episode_intro']['en']['text'] = "Hello, Caller! Welcome to New Day, New Standard, a show about the Domestic Workers Bill of Rights and what that means for you.  I am Christine Lewis; I am a nanny. And I am Miss Know-It-All.  You're about to listen to a new episode, but listen up. In case you want to go back to the list of episodes, press any key at any time. ";

$pph_prompts['p_episode_outro']['en']['text'] = "This is a very, very exciting moment for domestic workers. For the first time ever, domestic workers are recognized under the labor laws. New York domestic workers paved the way for every nanny, housekeeper, and elder caregiver across the country. Everyone has a stake in getting in on the action and keep blazing the trail of dignity and justice for the workers who make all other work possible. ";

$pph_prompts['p_outro_menu']['en']['text'] = 'To report an abuse, press 1. To share a positive story, press 2. To go back to the episode directory, press the pound key. ';

//-----------------------
//$p_definition[] = new VoipPrompt('Helloooo, Caller! I am Christine Lewis and in this episode of "New Day New Standard," we are going to define exactly what a "domestic worker" is.  Narrator, can ya define that for us, now?', 'woman');
$p_definition[] = new VoipPrompt('Helloooo, Caller! I am Christine Lewis and in this episode of New Day, New Standard, we are going to define exactly what a domestic worker is.  Narrator, can ya define that for us, now?', 'woman');


$p_definition[] = new VoipPrompt('Domestic workers are nannies, housekeepers, and elder caregivers who provide invaluable labor that frees others to work outside the home. In the state of New York, there are over 200 thousand domestic workers. Until now, domestic workers have largely been an invisible workforce in the eyes of the state. However, in November of 2010, the passage of the New York Domestic Worker Bill of Rights expanded labor protection for domestic workers and has raised public awareness of the problems of the industry.', 'man');

$p_definition[] = new VoipPrompt('You are probably wondering what that means for you.', 'woman');

$p_definition[] = new VoipPrompt('If you are a domestic worker, both the Fair Labor Standards ACT and New York Labor Law prohibit an employer from firing or otherwise retaliating against you for exercising your rights under wage and hour laws.', 'man');

$p_definition[] = new VoipPrompt('So if you are a domestic worker, this means you are now covered by a new set of laws, even if you are paid off the books!', 'woman');

$p_definition[] = new VoipPrompt('But remember to keep records of the hours you worked and the wages you were paid!', 'man');

$p_definition[] = new VoipPrompt('Thats right: this is a new day new standard. Its very exciting and you are part of a movement that is paving the path for others. If you are the employer of a domestic worker, this means that you have new responsibilities. Are ya complying?', 'woman');

//$pph_prompts['p_definition']['en']['text'] = $p_definition;

