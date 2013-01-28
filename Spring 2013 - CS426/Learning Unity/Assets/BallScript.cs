using UnityEngine;
using System.Collections;

public class BallScript : MonoBehaviour {
	
	public Vector3 force = new Vector3(10,0,0);
	bool startUpdating = false;
	
	// Use this for initialization
	void Start () {
		StartCoroutine(Wait(5));
	}
	
	// Update is called once per frame
	void Update () {
		if(startUpdating){
			transform.Translate(force * Time.deltaTime, Space.World);
			//Debug.Log("Force: "+force);
		}
	}
	
	void OnCollisionEnter(Collision collision){
		force = Vector3.Reflect(-force, collision.transform.forward);
		/*
		if(collision.gameObject.name == "Right Paddle" || collision.gameObject.name == "Left Paddle"){
			rigidbody.AddRelativeForce(-force);
			*/Debug.Log ("Ball collision with "+collision.gameObject.name+"!");/*
		}
		*/
	}
	
	IEnumerator Wait(int delay){
		Debug.Log("Waiting for "+delay+" seconds.");
		yield return new WaitForSeconds(5f);
		startUpdating = true;
		Debug.Log ("Resuming");
	}
}
