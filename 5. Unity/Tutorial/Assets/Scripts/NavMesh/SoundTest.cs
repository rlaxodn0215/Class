using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundTest : MonoBehaviour
{
    public AudioClip[] audioClip = null;
    private AudioSource audioSource = null;

    // Start is called before the first frame update
    void Start()
    {
        audioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        SoundTest_1();
    }

    void SoundTest_1()
    {
        if (Input.GetKeyDown(KeyCode.Keypad1))
        {
            StopAndPlay(audioClip[0]);
        }

        if (Input.GetKeyDown(KeyCode.Keypad2))
        {
            StopAndPlay(audioClip[1]);
        }

        if (Input.GetKeyDown(KeyCode.Keypad3))
        {
            StopAndPlay(audioClip[2]);
        }
    }

    void StopAndPlay(AudioClip clip)
    {
        audioSource.Stop();
        audioSource.clip = clip;
        audioSource.Play();
    }
}
