using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

public class Weapon : MonoBehaviour
{
    public int damage;

    public Camera camera;

    public float fireRate;

    private float nextFire;

    // Update is called once per frame
    void Update()
    {
        if (nextFire > 0)
            nextFire -= Time.deltaTime;

        if (Input.GetButton("Fire1") && nextFire <= 0)
        {
            nextFire = 1 / fireRate;

            Fire();
        }
    }

    void Fire()
    {
        Ray ray = new Ray(camera.transform.position, camera.transform.forward);

        RaycastHit hit;

        //Color color = new Color(1, 0, 0);

        //Debug.DrawRay(transform.position, transform.forward,color);

        if (Physics.Raycast(ray.origin, ray.direction, out hit, 100f))
        {

            // ¸ÂÀº À§Ä¡¿¡ ÃÑÅº ÈçÀû ¼ÒÈ¯
            //PhotonNetwork.Instantiate("prefabName", hit.point, Quaternion.identity);

            if (hit.transform.gameObject.GetComponent<Health>())
            {
                hit.transform.gameObject.GetComponent<PhotonView>().RPC("TakeDamage", RpcTarget.All, damage);
            }
        }
    }
}
