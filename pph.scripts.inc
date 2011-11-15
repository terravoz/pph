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
      $options['language'] = 'es';

      $script = new VoipScript('pph_welcome_script');
      $script->addSetVoice('woman');
      $script->addSet('max_session_duration', 0);

      // log the call
      $log_msg = t("Call from %caller_number on @date (id: %call_id)",
          array('@date' => format_date(time(), 'MDT')));
      $script->addLog($log_msg, 'PPH');

      $script->addSay(v('p_greetings'));

      $script->addLabel('language_selection');
      $p_main_menu = v('p_language_selection_menu');
      $input_options = array(
        '1' => 'spanish_version',
        '2' => 'english_version',
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($p_main_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('spanish_version');
      $script->addGosub('pph_main_menu_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('english_version');
      $options['language'] = 'en';
      $script->addGosub('pph_main_menu_script', $options);
      $script->addGoto('hang_up');

      $script->addLabel('invalid_option');
      $script->addGoto('hang_up');

      $script->addLabel('hang_up');
      $script->addHangup();
      break;

    case 'pph_main_menu_script':
      $script = new VoipScript('pph_main_menu_script');
      $language = $options['language'];

      $script->addLabel('introduction');
      $script->addGetInput(v('p_introduction', $language), 1);

      $script->addLabel('options_menu');
//TODO: what to do with strings that have a ' (like leo's car) in the middle?
      $p_options_menu = v('p_options_menu', $language);
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
      $p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('play_episodes');
      $script->addGosub('pph_episode_directory_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('report_abuse');
      $options['story_prompt'] = v('p_report_abuse', $language);
      $script->addGosub('pph_record_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('positive_story');
      $options['story_prompt'] = v('p_positive_story', $language);
      $script->addGosub('pph_record_story_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('resources');
      $script->addGosub('pph_resources_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('redirect_to_dwu');
      $script->addSay(v('p_redirecting', $language));
      $dwu_number = '+12124815747';
      $script->addDial($dwu_number);
      $script->addGoto('return');

      $script->addLabel('invalid_option');
      $script->addGoto('hang_up');

      $script->addLabel('hang_up');
      $script->addSay(v('p_thank_you', $language));

      $script->addLabel('return');
      $script->addReturn();
      break;

    case 'pph_episode_directory_script':
      $script = new VoipScript('pph_episode_directory_script');
      $language = $options['language'];

      $script->addLabel('episode_directory');
      $p_options_menu = v('p_episode_directory', $language);
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
      $p_invalid_msg = v('p_invalid_msg');
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
      $language = $options['language'];

      switch($story_id) {
        default:
$script->addSay("Invalid story id: $story_id. ");
$script->addLog("Invalid story id: $story_id. ");
return;
          break;
        case 'definition':
          $prompt = v('p_definition', $language);
          break;
        case 'minimum_wages':
          $prompt = v('p_minimum_wages', $language);
          break;
        case 'overtime_wages':
          $prompt = v('p_overtime_wages', $language);
          break;
        case 'taxes':
          $prompt = v('p_taxes', $language);
          break;
        case 'wage_deduction':
          $prompt = v('p_wage_deduction', $language);
          break;
        case 'insurance':
          $prompt = v('p_insurance', $language);
          break;
        case 'penalties':
          $prompt = v('p_penalties', $language);
          break;
        case 'immigration':
          $prompt = v('p_immigration', $language);
          break;
      }
      $script->addLabel('play_story');
      $p_episode_intro = v('p_episode_intro', $language);
      $p_episode_outro = v('p_episode_outro', $language);
      $p_episode_prompt = "$p_episode_intro $prompt $p_episode_outro";
      
      $script->addGetInput($p_episode_prompt, 1, '#', 1);
      $script->addGoto('go_back');

/****
      $script->addLabel('playback_menu');
      $p_options_menu = v('p_outro_menu', $language);
      $input_options = array(
        '1' => 'play_story',
        '#' => 'go_back',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('p_invalid_msg');
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
      $language = $options['language'];

      $script->addLabel('start');
      $prompt = $options['story_prompt'];
      $timeout = 5;
      $end_key = '#';
      $max_length = 300; // TODO: max length of the story
      $script->addRecord($prompt, $timeout, $end_key, $max_length);

// TODO: process hang up on recording

      $script->addLabel('accept_menu');
      $prompt = v('p_recording_confirmation', $language);
      $input_options = array(
        '1' => 'play_recording',
        '2' => 'accept_recording',
        '*' => 'start',
        '#' => 'go_back',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('p_invalid_msg');
      $script->addRunIvrMenu($prompt, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('invalid_option');
      $script->addGoto('go_back');

      $script->addLabel('play_recording');
      $script->addSay(v('p_recording_playback'));
      $script->addSay('%recording_public_url');
      $script->addGoto('accept_menu');

      $script->addLabel('accept_recording');
      $encoded_options = addslashes(json_encode($options));
      $script->addSet('callback_result',
        "^_pph_recording_callback(%call_id, %recording_public_url, %recording_duration, '$encoded_options')");
// TODO: check callback result
      $script->addSay(v('p_story_accepted'));
      $script->addGoto('go_back');

      $script->addLabel('go_back');
      $script->addReturn();
      break;

    case 'pph_resources_script':
      $script = new VoipScript('pph_resources_script');
      $language = $options['language'];

$script->addSay(v('p_resources_menu', $language));
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


