using UnityEngine;
using System.Collections;

public class PaddleScript : MonoBehaviour {
	
	public int speed = 10;
	public float topBound = (float)4.45;
	public float botBound = (float)-4.45;
	public float xPos = 0;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		
		if(Input.GetKey(KeyCode.W) && !Input.GetKey(KeyCode.S) && transform.position.z < topBound){
			float translation = Input.GetAxis("Vertical") * speed;
			translation *= Time.deltaTime;
			transform.Translate(0, 0, translation);
		}
		else if(Input.GetKey(KeyCode.S) && !Input.GetKey(KeyCode.W) && transform.position.z > botBound){
			float translation = Input.GetAxis("Vertical") * speed;
			translation *= Time.deltaTime;
			transform.Translate(0, 0, translation);
		}
		
	}
}
