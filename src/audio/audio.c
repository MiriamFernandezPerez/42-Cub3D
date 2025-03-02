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

void	play_sound(char audio_id, bool play, bool loop, t_data *data)
{
	t_audio	*audio;

	audio = get_audio(audio_id, data);
	if (!audio)
		return ;
	if (loop)
		BASS_ChannelFlags(audio->bass_id, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	if (play)
		BASS_ChannelPlay(audio->bass_id, 0);
	else
		BASS_ChannelPause(audio->bass_id);
}

void	stop_audio(char	audio_id, t_data *data)
{
	t_audio *audio;

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
	/*add_audio_node(TITLE_AUDIO, BASS_StreamCreateFile(FALSE,
			TITLE_PATH, 0, 0, 0), data);*/
	audio = data->audio_list;
	while (audio)
	{
		if (audio->bass_id == 0)
			ft_error_exit(ERR_BASS_FILE, data);
		audio = audio->next;
	}
	//printf("Audio handle %d\n", sound);
	//printf("BASS inició correctamente\n");
}
