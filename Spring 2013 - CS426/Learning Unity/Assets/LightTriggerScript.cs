using UnityEngine;
using System.Collections;

public class LightTriggerScript : MonoBehaviour {
	public bool lightEnabled = false;
	public Color lightColor = Color.green;
	
	// Use this for initialization
	void Start () {
		light.enabled = lightEnabled;
		light.color = lightColor;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
	
	void OnTriggerEnter(Collider collision){
		lightEnabled = !lightEnabled;
		light.enabled = lightEnabled;
		Debug.Log("Trigger enter"+collision);
	}
}

