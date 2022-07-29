using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotarCubo : MonoBehaviour
{
    public List<GameObject> ListaCubos;
    public bool desactivado = true;
    int[] ListaCubos2 = {0,1,2,9,10,11,18,19,20}; //ORDEN DE LOS CUBOS SEGUN Y
    int[] ListaCubos3 = {0,3,6,9,12,15,18,21,24}; //ORDEN DE LOS CUBOS SEGUN X

    void Update()
    {
        /*       PARA EL EJE Z     */
        if (Input.GetKeyDown(KeyCode.T) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 0; i < 9; i++) {
                ListaCubos[i].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(0, 0, 1), 90, 1.0f));

        }
        else if (Input.GetKey(KeyCode.Y) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 9; i < 18; i++) {
                ListaCubos[i].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(0, 0, 1), 90, 1.0f));
        }
        else if (Input.GetKey(KeyCode.U) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 18; i < 27; i++) {
                ListaCubos[i].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(0, 0, 1), 90, 1.0f));
        }

        /*       PARA EL EJE Y     */
        else if (Input.GetKey(KeyCode.G) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 0; i < 9; i++)
            {
                ListaCubos[ListaCubos2[i]].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(0, 1, 0), 90, 1.0f));
        }
        else if (Input.GetKey(KeyCode.H) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 0; i < 9; i++) {
                ListaCubos[ListaCubos2[i] + 3].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(0, 1, 0), 90, 1.0f));
        }
        else if (Input.GetKey(KeyCode.J) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 0; i < 9; i++) {
                ListaCubos[ListaCubos2[i] + 6].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(0, 1, 0), 90, 1.0f));
        }

        /*       PARA EL EJE X     */
        else if (Input.GetKeyDown(KeyCode.B) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 0; i < 9; i++) {
                ListaCubos[ListaCubos3[i]].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(1, 0, 0), 90, 1.0f));
        }
        else if (Input.GetKey(KeyCode.N) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++){
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 0; i < 9; i++) {
                ListaCubos[ListaCubos3[i] + 1].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(1, 0, 0), 90, 1.0f));
        }
        else if (Input.GetKey(KeyCode.M) && desactivado) {
            for (int i = 0; i < ListaCubos.Count; i++) {
                ListaCubos[i].transform.parent = null;
            }
            for (int i = 0; i < 9; i++) {
                ListaCubos[ListaCubos3[i] + 2].transform.parent = transform;
            }
            StartCoroutine(Rotate(new Vector3(1, 0, 0), 90, 1.0f));
        }

    }

    IEnumerator Rotate(Vector3 axis, float angle, float duration = 1.0f)
    {
        desactivado = false;

        Quaternion from = transform.rotation;
        Quaternion to = transform.rotation;
        to *= Quaternion.Euler(axis * angle);

        float elapsed = 0.0f;
        while (elapsed < duration)
        {
            transform.rotation = Quaternion.Slerp(from, to, elapsed / duration);
            elapsed += Time.deltaTime;
            yield return null;
        }
        transform.rotation = to;

        desactivado = true;
    }
}