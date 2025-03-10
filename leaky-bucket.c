#include <stdio.h>

int main()
{
    int queries, storage, out_pkt_size = 0;
    int in_pkt_size, bucket_size, remaining = 0;

    storage = 0; // init packets in the bucket.
    queries = 4; // no of time bucket content is checked.
    bucket_size = 10; // tot no of packets a bucket can accommodate.
    in_pkt_size = 4;// no packets enters the bucket at a time.
    out_pkt_size = 1;// no packets exits the bucket at a time.

    for(int i = 0 ; i < queries ; i++)
    {
        remaining = bucket_size - storage;
        if(in_pkt_size <= remaining)
            storage += in_pkt_size;
        else
            printf("\nPacket Loss!! %d\n", in_pkt_size);

        printf("\nBufer Size = %d \nOutput Bucket Size = %d\n", storage, bucket_size);
        storage -= out_pkt_size;
    }

    return 0;
}