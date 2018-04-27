/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:45:04 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/27 19:55:46 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __COLOR_H
# define __COLOR_H
# define RESET 				"\x1b[0m"
# define RED     			"\x1b[31m"
# define GREEN   			"\x1b[32m"
# define YELLOW  			"\x1b[33m"
# define BLUE    			"\x1b[34m"
# define MAGENTA 			"\x1b[35m"
# define CYAN    			"\x1b[36m"
# define WHITE    			"\x1b[37m"
# define RED_BOLD     		"\x1b[1;31m"
# define GREEN_BOLD   		"\x1b[1;32m"
# define YELLOW_BOLD  		"\x1b[1;33m"
# define BLUE_BOLD    		"\x1b[1;34m"
# define MAGENTA_BOLD 		"\x1b[1;35m"
# define CYAN_BOLD    		"\x1b[1;36m"
# define WHITE_BOLD   		"\x1b[1;37m"
# define WHITE_BK_RED_FG    "\x1b[47;31m"
# define BLUE_BK_WHITE_FG   "\x1b[44;37m"
# define GREEN_BK_YELLOW_FG "\x1b[42;33m"
# define COL_ALICEBLUE 0.941f, 0.973f, 1.000f
# define COL_ANTIQUEWHITE 0.980f, 0.922f, 0.843f
# define COL_AQUA 0.000f, 1.000f, 1.000f
# define COL_AQUAMARINE 0.498f, 1.000f, 0.831f
# define COL_AZURE 0.941f, 1.000f, 1.000f
# define COL_BEIGE 0.961f, 0.961f, 0.863f
# define COL_BISQUE 1.000f, 0.894f, 0.769f
# define COL_BLACK 0.000f, 0.000f, 0.000f
# define COL_BLANCHEDALMOND 1.000f, 0.922f, 0.804f
# define COL_BLUE 0.000f, 0.000f, 1.000f
# define COL_BLUEVIOLET 0.541f, 0.169f, 0.886f
# define COL_BROWN 0.647f, 0.165f, 0.165f
# define COL_BURLYWOOD 0.871f, 0.722f, 0.529f
# define COL_CADETBLUE 0.373f, 0.620f, 0.627f
# define COL_CHARTREUSE 0.498f, 1.000f, 0.000f
# define COL_CHOCOLATE 0.824f, 0.412f, 0.118f
# define COL_CORAL 1.000f, 0.498f, 0.314f
# define COL_CORNFLOWERBLUE 0.392f, 0.584f, 0.929f
# define COL_CORNSILK 1.000f, 0.973f, 0.863f
# define COL_CRIMSON 0.863f, 0.078f, 0.235f
# define COL_CYAN 0.000f, 1.000f, 1.000f
# define COL_DARKBLUE 0.000f, 0.000f, 0.545f
# define COL_DARKCYAN 0.000f, 0.545f, 0.545f
# define COL_DARKGOLDENROD 0.722f, 0.525f, 0.043f
# define COL_DARKGRAY 0.663f, 0.663f, 0.663f
# define COL_DARKGREEN 0.000f, 0.392f, 0.000f
# define COL_DARKGREY 0.663f, 0.663f, 0.663f
# define COL_DARKKHAKI 0.741f, 0.718f, 0.420f
# define COL_DARKMAGENTA 0.545f, 0.000f, 0.545f
# define COL_DARKOLIVEGREEN 0.333f, 0.420f, 0.184f
# define COL_DARKORANGE 1.000f, 0.549f, 0.000f
# define COL_DARKORCHID 0.600f, 0.196f, 0.800f
# define COL_DARKRED 0.545f, 0.000f, 0.000f
# define COL_DARKSALMON 0.914f, 0.588f, 0.478f
# define COL_DARKSEAGREEN 0.561f, 0.737f, 0.561f
# define COL_DARKSLATEBLUE 0.282f, 0.239f, 0.545f
# define COL_DARKSLATEGRAY 0.184f, 0.310f, 0.310f
# define COL_DARKSLATEGREY 0.184f, 0.310f, 0.310f
# define COL_DARKTURQUOISE 0.000f, 0.808f, 0.820f
# define COL_DARKVIOLET 0.580f, 0.000f, 0.827f
# define COL_DEEPPINK 1.000f, 0.078f, 0.576f
# define COL_DEEPSKYBLUE 0.000f, 0.749f, 1.000f
# define COL_DIMGRAY 0.412f, 0.412f, 0.412f
# define COL_DIMGREY 0.412f, 0.412f, 0.412f
# define COL_DODGERBLUE 0.118f, 0.565f, 1.000f
# define COL_FIREBRICK 0.698f, 0.133f, 0.133f
# define COL_FLORALWHITE 1.000f, 0.980f, 0.941f
# define COL_FORESTGREEN 0.133f, 0.545f, 0.133f
# define COL_FUCHSIA 1.000f, 0.000f, 1.000f
# define COL_GAINSBORO 0.863f, 0.863f, 0.863f
# define COL_GHOSTWHITE 0.973f, 0.973f, 1.000f
# define COL_GOLD 1.000f, 0.843f, 0.000f
# define COL_GOLDENROD 0.855f, 0.647f, 0.125f
# define COL_GRAY 0.502f, 0.502f, 0.502f
# define COL_GREEN 0.000f, 0.502f, 0.000f
# define COL_GREENYELLOW 0.678f, 1.000f, 0.184f
# define COL_GREY 0.502f, 0.502f, 0.502f
# define COL_HONEYDEW 0.941f, 1.000f, 0.941f
# define COL_HOTPINK 1.000f, 0.412f, 0.706f
# define COL_INDIANRED 0.804f, 0.361f, 0.361f
# define COL_INDIGO 0.294f, 0.000f, 0.510f
# define COL_IVORY 1.000f, 1.000f, 0.941f
# define COL_KHAKI 0.941f, 0.902f, 0.549f
# define COL_LAVENDER 0.902f, 0.902f, 0.980f
# define COL_LAVENDERBLUSH 1.000f, 0.941f, 0.961f
# define COL_LAWNGREEN 0.486f, 0.988f, 0.000f
# define COL_LEMONCHIFFON 1.000f, 0.980f, 0.804f
# define COL_LIGHTBLUE 0.678f, 0.847f, 0.902f
# define COL_LIGHTCORAL 0.941f, 0.502f, 0.502f
# define COL_LIGHTCYAN 0.878f, 1.000f, 1.000f
# define COL_LIGHTGOLDENRODYELLOW 0.980f, 0.980f, 0.824f
# define COL_LIGHTGRAY 0.827f, 0.827f, 0.827f
# define COL_LIGHTGREEN 0.565f, 0.933f, 0.565f
# define COL_LIGHTGREY 0.827f, 0.827f, 0.827f
# define COL_LIGHTPINK 1.000f, 0.714f, 0.757f
# define COL_LIGHTSALMON 1.000f, 0.627f, 0.478f
# define COL_LIGHTSEAGREEN 0.125f, 0.698f, 0.667f
# define COL_LIGHTSKYBLUE 0.529f, 0.808f, 0.980f
# define COL_LIGHTSLATEGRAY 0.467f, 0.533f, 0.600f
# define COL_LIGHTSLATEGREY 0.467f, 0.533f, 0.600f
# define COL_LIGHTSTEELBLUE 0.690f, 0.769f, 0.871f
# define COL_LIGHTYELLOW 1.000f, 1.000f, 0.878f
# define COL_LIME 0.000f, 1.000f, 0.000f
# define COL_LIMEGREEN 0.196f, 0.804f, 0.196f
# define COL_LINEN 0.980f, 0.941f, 0.902f
# define COL_MAGENTA 1.000f, 0.000f, 1.000f
# define COL_MAROON 0.502f, 0.000f, 0.000f
# define COL_MEDIUMAQUAMARINE 0.400f, 0.804f, 0.667f
# define COL_MEDIUMBLUE 0.000f, 0.000f, 0.804f
# define COL_MEDIUMORCHID 0.729f, 0.333f, 0.827f
# define COL_MEDIUMPURPLE 0.576f, 0.439f, 0.859f
# define COL_MEDIUMSEAGREEN 0.235f, 0.702f, 0.443f
# define COL_MEDIUMSLATEBLUE 0.482f, 0.408f, 0.933f
# define COL_MEDIUMSPRINGGREEN 0.000f, 0.980f, 0.604f
# define COL_MEDIUMTURQUOISE 0.282f, 0.820f, 0.800f
# define COL_MEDIUMVIOLETRED 0.780f, 0.082f, 0.522f
# define COL_MIDNIGHTBLUE 0.098f, 0.098f, 0.439f
# define COL_MINTCREAM 0.961f, 1.000f, 0.980f
# define COL_MISTYROSE 1.000f, 0.894f, 0.882f
# define COL_MOCCASIN 1.000f, 0.894f, 0.710f
# define COL_NAVAJOWHITE 1.000f, 0.871f, 0.678f
# define COL_NAVY 0.000f, 0.000f, 0.502f
# define COL_OLDLACE 0.992f, 0.961f, 0.902f
# define COL_OLIVE 0.502f, 0.502f, 0.000f
# define COL_OLIVEDRAB 0.420f, 0.557f, 0.137f
# define COL_ORANGE 1.000f, 0.647f, 0.000f
# define COL_ORANGERED 1.000f, 0.271f, 0.000f
# define COL_ORCHID 0.855f, 0.439f, 0.839f
# define COL_PALEGOLDENROD 0.933f, 0.910f, 0.667f
# define COL_PALEGREEN 0.596f, 0.984f, 0.596f
# define COL_PALETURQUOISE 0.686f, 0.933f, 0.933f
# define COL_PALEVIOLETRED 0.859f, 0.439f, 0.576f
# define COL_PAPAYAWHIP 1.000f, 0.937f, 0.835f
# define COL_PEACHPUFF 1.000f, 0.855f, 0.725f
# define COL_PERU 0.804f, 0.522f, 0.247f
# define COL_PINK 1.000f, 0.753f, 0.796f
# define COL_PLUM 0.867f, 0.627f, 0.867f
# define COL_POWDERBLUE 0.690f, 0.878f, 0.902f
# define COL_PURPLE 0.502f, 0.000f, 0.502f
# define COL_RED 1.000f, 0.000f, 0.000f
# define COL_ROSYBROWN 0.737f, 0.561f, 0.561f
# define COL_ROYALBLUE 0.255f, 0.412f, 0.882f
# define COL_SADDLEBROWN 0.545f, 0.271f, 0.075f
# define COL_SALMON 0.980f, 0.502f, 0.447f
# define COL_SANDYBROWN 0.957f, 0.643f, 0.376f
# define COL_SEAGREEN 0.180f, 0.545f, 0.341f
# define COL_SEASHELL 1.000f, 0.961f, 0.933f
# define COL_SIENNA 0.627f, 0.322f, 0.176f
# define COL_SILVER 0.753f, 0.753f, 0.753f
# define COL_SKYBLUE 0.529f, 0.808f, 0.922f
# define COL_SLATEBLUE 0.416f, 0.353f, 0.804f
# define COL_SLATEGRAY 0.439f, 0.502f, 0.565f
# define COL_SLATEGREY 0.439f, 0.502f, 0.565f
# define COL_SNOW 1.000f, 0.980f, 0.980f
# define COL_SPRINGGREEN 0.000f, 1.000f, 0.498f
# define COL_STEELBLUE 0.275f, 0.510f, 0.706f
# define COL_TAN 0.824f, 0.706f, 0.549f
# define COL_TEAL 0.000f, 0.502f, 0.502f
# define COL_THISTLE 0.847f, 0.749f, 0.847f
# define COL_TOMATO 1.000f, 0.388f, 0.278f
# define COL_TURQUOISE 0.251f, 0.878f, 0.816f
# define COL_VIOLET 0.933f, 0.510f, 0.933f
# define COL_WHEAT 0.961f, 0.871f, 0.702f
# define COL_WHITE 1.000f, 1.000f, 1.000f
# define COL_WHITESMOKE 0.961f, 0.961f, 0.961f
# define COL_YELLOW 1.000f, 1.000f, 0.000f
# define COL_YELLOWGREEN 0.604f, 0.804f, 0.196f

#endif
