/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_event.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:34:06 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/20 19:02:11 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.c"

void	UI_event()
{
	if(e.type == SDL_TEXTINPUT)
	{
		//Not copy or pasting
		// if(!( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ))
		// {
			text = ft_strcpy(e.text.text);
			renderText = true;
		// }
	}
	//Rerender text if needed
	if( renderText )
	{
		//Text is not empty
		if( inputText != "" )
		{
		    //Render new text
		    gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
		}
		//Text is empty
		else
		{
		    //Render space texture
		    gInputTextTexture.loadFromRenderedText( " ", textColor );
		}
}