<?php


/**
 * Implementation of hook_voipscript_get_script_names()
 */
function pph_voipscript_get_script_names() {
  $script_names[] = 'pph_welcome_script';
  $script_names[] = 'pph_main_menu_script';
  $script_names[] = 'pph_episode_directory_script';
  $script_names[] = 'pph_play_story_script';
  $script_names[] = 'pph_record_story_script';
  return $script_names;
}

/**
 * Implementation of hook_voipscript_load_script()
 */
function pph_voipscript_load_script($script_name, $options=NULL) {

  require_once(dirname(__FILE__) . DIRECTORY_SEPARATOR . 'pph.prompts.inc');

  $script = NULL;
  switch($script_name) {
    default:
      break;

    case 'pph_welcome_script':
      //$options['language'] = 'es';
      $options['voice'] = 'pph-spanish';
      $voipvoice = VoipVoice::getVoice('pph-spanish');
      voipvoice_set_current_voice($voipvoice);

      $script = new VoipScript('pph_welcome_script');
      $script->addSetVoice('woman');
      $script->addSet('max_session_duration', 0);

      // log the call
      $log_msg = t("Call from %caller_number on @date (id: %call_id)",
          array('@date' => format_date(time(), 'MDT')));
      $script->addLog($log_msg, 'PPH');

      $greetings[] =  new VoipPrompt(v('Welcome to New Day New Standard, a show about the Domestic Workers Bill of Rights. ', NULL, 'pph'));
      $greetings[] =  new VoipPrompt(v('Bienvenido a Nueva Ley, Nuevo Amanecer, un programa sobre la Carta de Derechos de las Trabajadoras del Hogar. '), NULL, 'es');
      
      $script->addSay($greetings);

      $script->addLabel('language_selection');
      $p_main_menu[] = new VoipPrompt(v("Para Espanol, oprima el numero 1. "), NULL, 'es');
      $p_main_menu[] = new VoipPrompt(v("For English, press 2. ", NULL, 'pph'));
      $input_options = array(
        '1' => 'spanish_version',
        '2' => 'english_version',
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('Invalid option selected', NULL, 'pph');
      //$p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($p_main_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('spanish_version');
      $script->addGosub('pph_main_menu_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('english_version');
      //$options['language'] = 'en';
      $options['voice'] = 'pph';
      $script->addGosub('pph_main_menu_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('invalid_option');
      $script->addGoto('hang_up');

      $script->addLabel('hang_up');
      $script->addHangup();
      break;

    case 'pph_main_menu_script':
      $script = new VoipScript('pph_main_menu_script');
      //$language = $options['language'];
      $voice =  $options['voice'];
      $voipvoice = VoipVoice::getVoice($voice);
      voipvoice_set_current_voice($voipvoice);
      
      $script->addLabel('introduction');
      $script->addGetInput(v("New Day New Standard is an interactive talk show about the new Domestic Workers Bill of Rights. I am Christine. "
      . " And I am Miss Know it All. During this talk show, you get to use your telephone to learn about different parts of the law. "
      . " as well as share your stories and be connected with Domestic Workers United. There is also more info online at w w w dot know your rights n y dot org. "), 1);
      //TODO: Translation of this must be done through Drupal locale interface
      //$script->addGetInput(v('p_introduction', $language), 1);

      $script->addLabel('options_menu');
//TODO: what to do with strings that have a ' (like leo's car) in the middle?
      //$p_options_menu = v('p_options_menu', $language);
      $p_options_menu = v("Main menu. To hear exciting episodes about the Domestic Workers Bill of Rights, press 1. To report an abuse, press 2. To share a positive story, press 3. To learn about resources for domestic workers and domestic employers, press 4. To speak directly to someone at the Domestic Workers United office, press 5. To hang up press the pound key. ");
      $input_options = array(
        '1' => 'play_episodes',
        '2' => 'report_abuse',
        '3' => 'positive_story',
        '4' => 'resources',
        '5' => 'redirect_to_dwu',
        '#' => 'hang_up',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      //$p_invalid_msg = v('p_invalid_msg');
      $p_invalid_msg = v('Invalid option selected');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('play_episodes');
      $script->addGosub('pph_episode_directory_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('report_abuse');
      //TODO: Translation of this must be done through Drupal locale interface
      $options['story_prompt'] = v('Please record your name and your abuse story after the beep. When done, press the pound key.');
      $script->addGosub('pph_record_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('positive_story');

      $options['story_prompt'] = v('Please record your name and your positive story after the beep. When done, press the pound key.');
      $script->addGosub('pph_record_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('resources');
      $script->addGosub('pph_resources_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('redirect_to_dwu');
      $script->addSay(v('Redirecting to DWU office'));
      $dwu_number = '+12124815747';
      $script->addDial($dwu_number);
      $script->addGoto('return');

      $script->addLabel('invalid_option');
      $script->addGoto('hang_up');

      $script->addLabel('hang_up');
      $script->addSay(v('Thank you for calling New Day New Standard. For more information about this show or about Domestic Workers United go to h t t p know your rights n y dot org or call 2 1 2 4 8 1 5 7 4 7. '));

      $script->addLabel('return');
      $script->addReturn();
      break;

    case 'pph_episode_directory_script':
      $script = new VoipScript('pph_episode_directory_script');
      $voice =  $options['voice'];
      $voipvoice = VoipVoice::getVoice($voice);
      voipvoice_set_current_voice($voipvoice);
      
      $script->addLabel('episode_directory');

      $p_options_menu = v("Episode directory. "
. "To hear about the definition of a domestic worker, press 1. "
. "To hear about minimum wages, press 2. "
. "To hear about overtime wages, press 3. "
. "To hear about paying your taxes, press 4. "
. "To hear about wage deductions, press 5. "
. "To hear about unemployment insurance, press 6. "
. "To hear about penalties for employers who do not comply with the law, press 7. "
. "To hear about immigration issues for domestic workers, trafficking, and modern day slavery, press 8. "
. "You can also find copies of contracts, guidelines, and other resources at w w w dot know your rights n y dot org. "
. "To go back to the main menu, press the pound key. ");

      $input_options = array(
        '1' => 'definition',
        '2' => 'minimum_wages',
        '3' => 'overtime_wages',
        '4' => 'taxes',
        '5' => 'wage_deduction',
        '6' => 'insurance',
        '7' => 'penalties',
        '8' => 'immigration',
        '#' => 'go_back',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      //$p_invalid_msg = v('p_invalid_msg');
      $p_invalid_msg = v('Invalid option selected');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('definition');
      $options['story_id'] = 'definition';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('minimum_wages');
      $options['story_id'] = 'minimum_wages';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('overtime_wages');
      $options['story_id'] = 'overtime_wages';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('taxes');
      $options['story_id'] = 'taxes';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('wage_deduction');
      $options['story_id'] = 'wage_deduction';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('insurance');
      $options['story_id'] = 'insurance';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('penalties');
      $options['story_id'] = 'penalties';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('immigration');
      $options['story_id'] = 'immigration';
      $script->addGosub('pph_play_story_script', $options);
      $script->addGoto('episode_directory');

      $script->addLabel('invalid_option');
      $script->addGoto('go_back');

// todo: should the system return or hangup here?
      $script->addLabel('go_back');
      $script->addReturn();
      break;

    case 'pph_play_story_script':
      $script = new VoipScript('pph_play_story_script');
      $story_id = $options['story_id'];
      $voice =  $options['voice'];
      $voipvoice = VoipVoice::getVoice($voice);
      voipvoice_set_current_voice($voipvoice);

      switch($story_id) {
        default:
$script->addSay("Invalid story id: $story_id. ");
$script->addLog("Invalid story id: $story_id. ");
return;
          break;
        case 'definition':
          $prompt = v('Here the system will play an episode about definition of a domestic worker. ');
          break;
        case 'minimum_wages':
          $prompt = v('Here the system will play an episode about minimum wages. ');
          break;
        case 'overtime_wages':
           $prompt = v('Here the system will play an episode about overtime wages. ');
          break;
        case 'taxes':
         //TODO: p_taxes missing
          //$prompt = v('p_taxes', $language);
          //$prompt = v('', NULL, $voice);
          break;
        case 'wage_deduction':
          $prompt = v('Here the system will play an episode about wage deduction. ');
          break;
        case 'insurance':
          $prompt = v('Here the system will play an episode about insurance. ');
          break;
        case 'penalties':
          $prompt = v('Here the system will play an episode about penalties for employers. ');
          break;
        case 'immigration':
          $prompt = v('Here the system will play an episode about immigration. ');
          break;
      }
      $script->addLabel('play_story');
      $p_episode_intro = v("Hello, Caller! Welcome to New Day, New Standard, a show about the Domestic Workers Bill of Rights and what that means for you.  I am Christine Lewis; I am a nanny. And I am Miss Know-It-All.  You're about to listen to a new episode, but listen up. In case you want to go back to the list of episodes, press any key at any time. ");
      $p_episode_outro = v('This show has been produced by People\'s Production House for Domestic Workers United. I also want to thank National 
      Employment Law Project, Urban Justice Center, and Jews for Racial and Economic Justice for their assistance in producing this show. This is a very,
      very exciting moment for domestic workers. For the first time ever, domestic workers are recognized under the labor laws. 
      New York domestic workers paved the way for every nanny, housekeeper, and elder caregiver across the country. 
      Everyone has a stake in getting in on the action and keep blazing the trail of dignity and justice for the workers who make all other work 
      possible. ');
      $p_episode_prompt = "$p_episode_intro $prompt $p_episode_outro";
      
      $script->addGetInput($p_episode_prompt, 1, '#', 1);
      $script->addGoto('go_back');

/****
      $script->addLabel('playback_menu');
      //$p_options_menu = v('p_outro_menu', $language);
      $p_options_menu = v('To report an abuse, press 1. To share a positive story, press 2. To go back to the episode directory, press the pound key. ', NULL, $voice);
      $input_options = array(
        '1' => 'play_story',
        '#' => 'go_back',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      //$p_invalid_msg = v('p_invalid_msg');
      $p_invalid_msg = v('Invalid option selected', NULL, 'pph');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('invalid_option');
      $script->addGoto('go_back');
****/

      $script->addLabel('go_back');
      $script->addReturn();
      break;

    case 'pph_record_story_script':
      $script = new VoipScript('pph_record_story_script');
     // $language = $options['language'];
      $voice =  $options['voice'];
      $voipvoice = VoipVoice::getVoice($voice);
      voipvoice_set_current_voice($voipvoice);

      $script->addLabel('start');
      $prompt = $options['story_prompt'];
      $timeout = 5;
      $end_key = '#';
      $max_length = 300; // TODO: max length of the story
      $script->addRecord($prompt, $timeout, $end_key, $max_length);

// TODO: What to do in case of hang up on recording? Get rid of the recording?

      $script->addLabel('accept_menu');
      $prompt = v('To hear your recording, press 1. To accept your recording, press 2. To record once again, press the star key.');
      $input_options = array(
        '1' => 'play_recording',
        '2' => 'accept_recording',
        '*' => 'start',
        '#' => 'go_back',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      //$p_invalid_msg = v('p_invalid_msg');
      $p_invalid_msg = v('Invalid option selected');
      $script->addRunIvrMenu($prompt, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('invalid_option');
      $script->addGoto('go_back');

      $script->addLabel('play_recording');
      //$script->addSay(v('p_recording_playback'));
      $script->addSay(v('This is what you recorded: '));
      $script->addSay('%recording_public_url');
      $script->addGoto('accept_menu');

      $script->addLabel('accept_recording');
      $encoded_options = addslashes(json_encode($options));
      $script->addSet('callback_result',
        "^_pph_recording_callback(%call_id, %recording_public_url, %recording_duration, '$encoded_options')");
// TODO: check callback result
      //$script->addSay(v('p_story_accepted'));
      $script->addSay(v('Your story has been successfully recorded. '));
      $script->addGoto('go_back');

      $script->addLabel('go_back');
      $script->addReturn();
      break;

    case 'pph_resources_script':
      $script = new VoipScript('pph_resources_script');
      //$language = $options['language'];
      $voice =  $options['voice'];
      $voipvoice = VoipVoice::getVoice($voice);
      voipvoice_set_current_voice($voipvoice);
      
      $script->addSay(v('If you are an employer and you want to be connected to more resources, email Rachel at j f r e j dot org or visit domestic employers dot org. If you are a domestic worker and you want to have information about domestic workers meetings sent to the phone that you are calling on right now, press 1. To return to the main menu, press the pound key. '));
// TODO: finish this part of the script

      $script->addLabel('go_back');
      $script->addReturn();
      break;
  }

  return $script;
}

/**
 * Internal functions
 */

function _pph_recording_callback($call_id, $recording_url, $recording_duration, $encoded_options) {
watchdog('pph', "New story recorded for call id: $call_id, url: $recording_url, duration: $recording_duration");
// TODO: add type to recorded stories
/****
  $voipblog_options = (array)json_decode(stripslashes($encoded_options));
  $voipblog_options['node_type'] = 'memory';
  $voipblog_options['audio_field_name'] = 'field_memory_audio';
  $voipblog_options['voipblog_type'] = $voipblog_options['memory_type'];
  $voipblog_options['memory_destination'] = $destination_nid;
  $serialized_options = serialize($voipblog_options);
  $rc = voipblog_recording_callback($call_id, $recording_url, $recording_duration, $serialized_options);
****/
  return $rc;
}


