#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>

struct opvt2ahr
{
    unsigned short heading;
    signed short pitch, roll;
    signed long gyro_x, gyro_y, gyro_z;
    signed long acc_x, acc_y, acc_z;
    signed short mag_x, mag_y, mag_z;
    unsigned short USW;
    unsigned short vinp;
    signed short temp;
    signed long long latitude, longitude;
    signed long altitude, v_east, v_north, v_up;
    signed long long lat_GNSS, lon_GNSS;
    signed long alt_GNSS, vh_GNSS;
    signed short track_grnd;
    signed long vup_GNSS;
    unsigned long ms_gps;
    unsigned char GNSS_info1, GNSS_info2, solnSVs;
    unsigned short v_latency;
    unsigned char angle_pos_type;
    unsigned short hdg_GNSS;
    signed short latency_ms_hdg, latency_ms_pos, latency_ms_vel;
    unsigned short p_bar;
    unsigned long h_bar;
    unsigned char new_gps;
};

void payload2opvt2ahr(struct opvt2ahr *frame, unsigned char payload[129])
{
    if (!frame) return;

    frame->heading = payload[0] | (payload[1] << 8);
    frame->pitch = payload[2] | (payload[3] << 8);
    frame->roll = payload[4] | (payload[5] << 8);

    frame->gyro_x = payload[6] | (payload[7] << 8) |
        (payload[8] << 16) | (payload[9] << 24);
    frame->gyro_y = payload[10] | (payload[11] << 8) |
        (payload[12] << 16) | (payload[13] << 24);
    frame->gyro_z = payload[14] | (payload[15] << 8) |
        (payload[16] << 16) | (payload[17] << 24);

    frame->acc_x = payload[18] | (payload[19] << 8) |
        (payload[20] << 16) | (payload[21] << 24);
    frame->acc_y = payload[22] | payload[23] << 8 |
        (payload[24] << 16) | (payload[25] << 24);
    frame->acc_z = payload[26] | (payload[27] << 8) |
        (payload[28] << 16) | (payload[29] << 24);

    frame->mag_x = payload[30] | (payload[31] << 8);
    frame->mag_y = payload[32] | (payload[33] << 8);
    frame->mag_z = payload[34] | (payload[35] << 8);

    frame->USW = payload[36] | (payload[37] << 8);
    frame->vinp = payload[38] | (payload[39] << 8);
    frame->temp = payload[40] | (payload[41] << 8);

    frame->latitude = (long long) payload[42] |
        ((long long) payload[43] << 8) |
        ((long long) payload[44] << 16) |
        ((long long) payload[45] << 24) |
        ((long long) payload[46] << 32) |
        ((long long) payload[47] << 40) |
        ((long long) payload[48] << 48) |
        ((long long) payload[49] << 56);
    frame->longitude = (long long) payload[50] |
        ((long long) payload[51] << 8) |
        ((long long) payload[52] << 16) |
        ((long long) payload[53] << 24) |
        ((long long) payload[54] << 32) |
        ((long long) payload[55] << 40) |
        ((long long) payload[56] << 48) |
        ((long long) payload[57] << 56);
    frame->altitude = payload[58] | (payload[59] << 8) |
        (payload[60] << 16) | (payload[61]) << 24;

    frame->v_east = payload[62] | (payload[63] << 8) |
        (payload[64] << 16) | (payload[65] << 24);
    frame->v_north = payload[66] | (payload[67] << 8) |
        (payload[68] << 16) | (payload[69] << 24);
    frame->v_up = payload[70] | (payload[71] << 8) |
        (payload[72] << 16) | (payload[73] << 24);

    frame->lat_GNSS = (long long) payload[74] |
        ((long long) payload[75] << 8) |
        ((long long) payload[76] << 16) |
        ((long long) payload[77] << 24) |
        ((long long) payload[78] << 32) |
        ((long long) payload[79] << 40) |
        ((long long) payload[80] << 48) |
        ((long long) payload[81] << 56);
    frame->lon_GNSS = (long long) payload[82] |
        ((long long) payload[83] << 8) |
        ((long long) payload[84] << 16) |
        ((long long) payload[85] << 24) |
        ((long long) payload[86] << 32) |
        ((long long) payload[87] << 40) |
        ((long long) payload[88] << 48) |
        ((long long) payload[89] << 56);
    frame->alt_GNSS = payload[90] | (payload[91] << 8) |
        (payload[92] << 16) | (payload[93] << 24);

    frame->vh_GNSS = payload[94] | (payload[95] << 8) |
        (payload[96] << 16) | (payload[97] << 24);
    frame->track_grnd = payload[98] | (payload[99] << 8);
    frame->vup_GNSS = payload[100] | (payload[101] << 8) |
        (payload[102] << 16) | (payload[103] << 24);

    frame->ms_gps = payload[104] | (payload[105] << 8) |
        (payload[106] << 16) | (payload[107] << 24);
    frame->GNSS_info1 = payload[108];
    frame->GNSS_info2 = payload[109];
    frame->solnSVs = payload[110];
    frame->v_latency = payload[111] | (payload[112] << 8);
    frame->angle_pos_type = payload[113];
    frame->hdg_GNSS = payload[114] | (payload[115] << 8);

    frame->latency_ms_hdg = payload[116] | (payload[117] << 8);
    frame->latency_ms_pos = payload[118] | (payload[119] << 8);
    frame->latency_ms_vel = payload[120] | (payload[121] << 8);

    frame->p_bar = payload[122] | (payload[123] << 8);
    frame->h_bar = payload[124] | (payload[125] << 8) |
        (payload[126] << 16) | (payload[127] << 24);
    frame->new_gps = payload[128];
}

void println_opvt2ahr(FILE *out, struct opvt2ahr *frame)
{
    if (!frame)
    {
        fprintf(out,
               "        Heading"
               "          Pitch"
               "           Roll"
               "         Gyro_X"
               "         Gyro_Y"
               "         Gyro_Z"
               "          Acc_X"
               "          Acc_Y"
               "          Acc_Z"
               "         Magn_X"
               "         Magn_Y"
               "         Magn_Z"
               "    Temperature"
               "            Vdd"
               "      USW (L/H)"
               "       Latitude"
               "      Longitude"
               "       Altitude"
               "         V_East"
               "        V_North"
               "           V_Up"
               "       Lat_GNSS"
               "      Long_GNSS"
               "    Height_GNSS"
               "        Hor_spd"
               "        Trk_gnd"
               "        Ver_spd"
               "         ms_gps"
               "    GNSS_info_1"
               "    GNSS_info_2"
               "       #solnSVs"
               "        latency"
               "  anglesPosType"
               "   Heading_GNSS"
               "    Latency_ms_head"
               "     Latency_ms_pos"
               "     Latency_ms_vel"
               "          P_Bar"
               "          H_Bar"
               "        New_GPS\n");
        return;
    }

    fprintf(out, "%15.2f%15.2f%15.2f",
        frame->heading/100.0, frame->pitch/100.0, frame->roll/100.0);
    fprintf(out, "%15.5f%15.5f%15.5f",
        frame->gyro_x/1.0E5, frame->gyro_y/1.0E5, frame->gyro_z/1.0E5);
    fprintf(out, "%15.6f%15.6f%15.6f",
        frame->acc_x/1.0E6, frame->acc_y/1.0E6, frame->acc_z/1.0E6);
    fprintf(out, "%15.1f%15.1f%15.1f",
        frame->mag_x*10.0, frame->mag_y*10.0, frame->mag_z*10.0);
    fprintf(out, "%15.1f%15.2f%15hu",
        frame->temp/10.0, frame->vinp/100.0, frame->USW);
    fprintf(out, "%15.9f%15.9f%15.7f",
        frame->latitude/1.0E9, frame->longitude/1.0E9, frame->altitude/1.0E3);
    fprintf(out, "%15.2f%15.2f%15.2f",
        frame->v_east/100.0, frame->v_north/100.0, frame->v_up/100.0);
    fprintf(out, "%15.9f%15.9f%15.7f",
        frame->lat_GNSS/1.0E9, frame->lon_GNSS/1.0E9, frame->alt_GNSS/1.0E3);
    fprintf(out, "%15.2f%15.2f%15.2f",
        frame->vh_GNSS/100.0, frame->track_grnd/100.0, frame->vup_GNSS/100.0);
    fprintf(out, "%15lu", frame->ms_gps);
    fprintf(out, "%15hhu%15hhu",
        frame->GNSS_info1, frame->GNSS_info2);
    fprintf(out, "%15hhu%15hu%15hhu",
        frame->solnSVs, frame->v_latency, frame->angle_pos_type);
    fprintf(out, "%15.2f%19hhd%19hhd%19hhd",
        frame->hdg_GNSS/100.0, frame->latency_ms_hdg,
        frame->latency_ms_pos, frame->latency_ms_vel);
    fprintf(out, "%15lu%15.2f%15hhu\n",
        ((unsigned long) frame->p_bar)*2, frame->h_bar/100.0, frame->new_gps);
}

const char* argument_error =
    "%s: invalid option -- '%s'\n"
    "type '%s --usage' for more info\n";

const char* usage_help =
    "usage: %s infile [-o outfile]\n"
    "  infile: file to be converted to text\n"
    "  outfile: output filename\n";

int main(int argc, char** argv)
{
    if (argc < 2) // first argument must be infile
    {
        fprintf(stderr, "%s: must provide a filename first\n", argv[0]);
        return 1;
    }

    // special case: if first argument is "--usage", print the usage
    // help string to stderr
    if (strcmp(argv[1], "--usage") == 0)
    {
        printf(usage_help, argv[0]);
        return 0;
    }

    // open the OPVT2AHR/OPVT etc file; if can't open, return error
    FILE *infile = fopen(argv[1], "rb");
    if (!infile)
    {
        fprintf(stderr, "%s: failed to open '%s'\n", argv[0], argv[1]);
        return 1;
    }

    unsigned long long filelen;
    fseek(infile, 0, SEEK_END);
    filelen = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    if (filelen == 0)
    {
        fprintf(stderr, "%s: %s is an empty file\n", argv[0], argv[1]);
        return 1;
    }

    unsigned char out_index = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-o") | !strcmp(argv[i], "--out"))
        {
            if (argc < i + 2)
            {
                fprintf(stderr, usage_help, argv[0]);
                return 1;
            }
            out_index = i + 1;
        }
    }

    unsigned char *file_buffer = (unsigned char*) malloc(filelen);
    if (!file_buffer)
    {
        fprintf(stderr, "%s: memory allocation error\n", argv[0]);
        return 1;
    }

    fread(file_buffer, 1, filelen, infile);
    fclose(infile);

    char *outfn = (char*) malloc(strlen(argv[1]) + 1);
    if (!outfn)
    {
        fprintf(stderr, "%s: memory allocation error\n", argv[0]);
        return 1;
    }
    strcpy(outfn, argv[1]);
    char *ext_ptr = strstr(outfn, ".bin");
    if (!ext_ptr) // file does not contain ".bin", so tack ".txt" on the end
    {
        free(outfn);
        outfn = (char*) malloc(strlen(argv[1]) + 5);
        if (!outfn)
        {
            fprintf(stderr, "%s: memory allocation error\n", argv[0]);
            return 1;
        }
        strcpy(outfn, argv[1]);
        strcpy(outfn + strlen(outfn), ".txt");
    }
    else // replace ".bin" with ".txt"
    {
        strcpy(ext_ptr, ".txt");
    }

    FILE *outfile;
    if (out_index)
    {
        outfn = argv[out_index];
    }
    outfile = fopen(outfn, "wb");
    if (!outfile)
    {
        fprintf(stderr, "%s: failed to open '%s'\n", argv[0], outfn);
        return 1;
    }

    const unsigned long framelen = 129, alignlen = 50;
    signed long long rptr = alignlen;
    println_opvt2ahr(outfile, 0);
    while (rptr < filelen - framelen)
    {
        unsigned char payload[framelen];
        memcpy(payload, file_buffer + rptr, sizeof(payload));
        struct opvt2ahr frame;
        payload2opvt2ahr(&frame, payload);
        println_opvt2ahr(outfile, &frame);
        rptr += framelen;
        fprintf(stderr, "\rWriting to %s: %2lld%%", outfn, (100*rptr)/filelen);
    }
    fclose(outfile);
    fprintf(stderr, "\nDone.\n");
    return 0;
}
