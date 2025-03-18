/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:24:19 by mirifern          #+#    #+#             */
/*   Updated: 2025/03/01 18:24:22 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include "../../bass/bass.h"
#include "../../inc/audio.h"

void	play_sound(char id, bool play, bool loop, t_data *data)
{
	t_audio		*audio;
	HCHANNEL	channel;

	channel = 0;
	audio = get_audio(id, data);
	if (!audio || audio->bass_id == 0)
		return ;
	if (loop && id == TITLE_AUDIO)
		BASS_ChannelFlags(audio->bass_id, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	if (play)
	{
		if (id == DOOR_AUDIO || id == COLLECT_AUDIO
			|| id == KEY_AUDIO || id == LEVEL_AUDIO)
		{
			channel = BASS_SampleGetChannel(audio->bass_id, FALSE);
			if (channel)
				BASS_ChannelPlay(channel, FALSE);
		}
		else
			BASS_ChannelPlay(audio->bass_id, FALSE);
	}
	else
		BASS_ChannelPause(audio->bass_id);
}

void	stop_audio(char audio_id, t_data *data)
{
	t_audio	*audio;

	audio = get_audio(audio_id, data);
	if (!audio)
		return ;
	if (audio->bass_id != 0)
	{
		BASS_ChannelStop((audio->bass_id));
	}
}

void	init_audio(t_data *data)
{
	t_audio	*audio;

	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		return (ft_error_exit(ERR_BASS, data));
	add_audio_node(TITLE_AUDIO, BASS_StreamCreateFile(FALSE,
			TITLE_PATH, 0, 0, 0), data);
	add_audio_node(DOOR_AUDIO, BASS_SampleLoad(
			FALSE, DOOR_PATH, 0, 0, 3, BASS_SAMPLE_OVER_VOL), data);
	add_audio_node(SPRING_AUDIO, BASS_StreamCreateFile(
			FALSE, SPRING_PATH, 0, 0, 0), data);
	add_audio_node(UNLOCK_AUDIO, BASS_StreamCreateFile(
			FALSE, UNLOCK_PATH, 0, 0, 0), data);
	add_audio_node(SUMMER_AUDIO, BASS_StreamCreateFile(
			FALSE, SUMMER_PATH, 0, 0, 0), data);
	add_audio_node(AUTUMN_AUDIO, BASS_StreamCreateFile(
			FALSE, AUTUMN_PATH, 0, 0, 0), data);
	add_audio_node(WINTER_AUDIO, BASS_StreamCreateFile(
			FALSE, WINTER_PATH, 0, 0, 0), data);
	add_audio_node(COLLECT_AUDIO, BASS_SampleLoad(
			FALSE, COLLECT_PATH, 0, 0, 3, BASS_SAMPLE_OVER_VOL), data);
	add_audio_node(KEY_AUDIO, BASS_SampleLoad(
			FALSE, KEY_PATH, 0, 0, 3, BASS_SAMPLE_OVER_VOL), data);
	add_audio_node(LEVEL_AUDIO, BASS_SampleLoad(
			FALSE, LEVEL_PATH, 0, 0, 1, BASS_SAMPLE_OVER_VOL), data);
	audio = data->audio_list;
	while (audio)
	{
		if (audio->bass_id == 0)
			ft_error_exit(ERR_BASS_FILE, data);
		audio = audio->next;
	}
}
