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

void	play_sound(uint32_t sound, bool play, bool loop)
{
	if (!sound)
		return ;
	if (loop)
		BASS_ChannelFlags(sound, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
	if (play)
		BASS_ChannelPlay(sound, 0);
	else
		BASS_ChannelPause(sound);
}

void	stop_audio(uint32_t *audio, t_data *data)
{
	if ((*audio) != 0)
	{
		BASS_ChannelStop((*audio));
		(*audio) = 0;
		printf("start audio %d\n", data->audio->start_audio);
	}
}

void	init_audio_start(t_data *data)
{
	uint32_t	sound;

	sound = 0;
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		return (ft_error_exit(ERR_BASS, data));
	sound = BASS_StreamCreateFile(FALSE,
			"assets/audio/spring8bit.mp3", 0, 0, 0);
	if (sound == 0)
		return (ft_error_exit(ERR_BASS_FILE, data));
	else
		data->audio->start_audio = sound;
	//printf("Audio handle %d\n", sound);
	play_sound(sound, true, true);
	//printf("BASS inició correctamente\n");
}
