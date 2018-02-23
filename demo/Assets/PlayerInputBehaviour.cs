using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerInputBehaviour : MonoBehaviour
{
	public UnityEngine.UI.Text	player;
	public void	ChangeText(UnityEngine.UI.InputField field)
	{
		player.text = field.text;
	}
}
