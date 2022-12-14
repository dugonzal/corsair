/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:34:01 by vscode            #+#    #+#             */
/*   Updated: 2022/08/06 09:56:39 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corsair.h"


void rsa_gen_keys(void)
{
    int             ret = 0;
    RSA             *rsa = NULL;
    BIGNUM          *bignum = NULL;
    BIO             *bio_private = NULL;
    BIO             *bio_public = NULL;
    int              bits = 1024;

    bignum = BN_new();
    // rsa->n, rsa->e, rsa->d, rsa->p, rsa->q rsa->dmp1, rsa->dmq1, rsa->iqmp rsa_new() calculates n, e, d, p, q, dmp1, dmq1, iqmp from the public and private keys.
    ret = BN_set_word(bignum,RSA_F4);
    if(ret != 1)
	{
        goto cleanup;
    }
    rsa = RSA_new();
    ret = RSA_generate_key_ex(rsa, bits, bignum, NULL);
    if(ret != 1)
	{
        goto cleanup;
    }
    // write rsa private key to file
    bio_private = BIO_new_file("../keys/private.key", "w+");
    ret = PEM_write_bio_RSAPrivateKey(bio_private, rsa, NULL, NULL, 0, NULL, NULL);
    BIO_flush(bio_private);
    // write rsa public key to file
    bio_public = BIO_new_file("../keys/public.key", "w+");
    ret = PEM_write_bio_RSAPublicKey(bio_public, rsa);
    // imprimir modulo y exponente de la clave publica
    //BIO_printf(bio_public, "Modulo: %s\n", BN_bn2hex(rsa->n));
    //BIO_printf(bio_public, "Exponente: %s\n", BN_bn2hex(rsa->e));
    if(ret != 1)
	{
        goto cleanup;
    }
	//printf("RSA keys generated successfully\n");
    BIO_flush(bio_public);
	cleanup:
    BIO_free_all(bio_private);
    BIO_free_all(bio_public);
    RSA_free(rsa);
    BN_free(bignum);
}
