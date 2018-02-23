using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ResultBehaviour : MonoBehaviour
{
	public InputField	player1;
	public InputField	player2;
	public Text			player1Score;
	public Text			player2Score;

	private float		playerStart;

	void			Start()
	{
		playerStart = (-691 / 1492.0f) * Screen.width;
		ResetResult();
		Debug.Log(Screen.width + " " + Screen.height);
	}
	public void		UpdateResult(float p1, float p2, float count)
	{
		RectTransform t;

		t = player1.GetComponent<RectTransform>();
		player1.GetComponent<RectTransform>().offsetMax = new Vector2(playerStart * (1 - p1 / count), t.offsetMax.y);
        t = player2.GetComponent<RectTransform>();
        player2.GetComponent<RectTransform>().offsetMax = new Vector2(playerStart * (1 - p2 / count), t.offsetMax.y);
		player1Score.text = p1.ToString();
        player2Score.text = p2.ToString();
	}
	public void		ResetResult()
	{
		UpdateResult(0, 0, 1);
        player1Score.text = "";
        player2Score.text = "";
	}
}
