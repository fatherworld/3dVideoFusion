////main.cpp
//#include <stdio.h>
//#include <stdlib.h>
//
//#pragma comment(lib,"ffmpeg\\libs\\avutil.lib")
//#pragma comment(lib,"ffmpeg\\libs\\avformat.lib")
//#pragma comment(lib,"ffmpeg\\libs\\avcodec.lib")
//#pragma comment(lib,"ffmpeg\\libs\\swscale.lib")
//
//extern "C"
//{
//
//	//����
//#include "libavcodec/avcodec.h"
//	//��װ��ʽ����
//#include "libavformat/avformat.h"
//	//���ش���
//#include "libswscale/swscale.h"
//};
//
//
//int main1(int argc, char* argv[])
//{
//	//��ȡ��������ļ���
//	const char *input = "test.mp4";
//	const char *output = "test.yuv";
//	const char *input = "./images/1.mp4";
//
//
//	//1.ע���������
//	av_register_all();
//
//	//��װ��ʽ�����ģ�ͳ��ȫ�ֵĽṹ�壬��������Ƶ�ļ���װ��ʽ�������Ϣ
//	AVFormatContext *pFormatCtx = avformat_alloc_context();
//
//	//2.��������Ƶ�ļ�
//	if (avformat_open_input(&pFormatCtx, input, NULL, NULL) != 0)
//	{
//		printf("%s", "�޷���������Ƶ�ļ�");
//		return -1;
//	}
//
//	//3.��ȡ��Ƶ�ļ���Ϣ
//	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
//	{
//		printf("%s", "�޷���ȡ��Ƶ�ļ���Ϣ");
//		return -1;
//	}
//
//	//��ȡ��Ƶ��������λ��
//	//�����������͵�������Ƶ������Ƶ������Ļ�������ҵ���Ƶ��
//	int v_stream_idx = -1;
//	int i = 0;
//	//number of streams
//	for (; i < pFormatCtx->nb_streams; i++)
//	{
//		//��������
//		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
//		{
//			v_stream_idx = i;
//			break;
//		}
//	}
//
//	if (v_stream_idx == -1)
//	{
//		printf("%s", "�Ҳ�����Ƶ��\n");
//		return -1;
//	}
//
//	//ֻ��֪����Ƶ�ı��뷽ʽ�����ܹ����ݱ��뷽ʽȥ�ҵ�������
//	//��ȡ��Ƶ���еı����������
//	AVCodecContext *pCodecCtx = pFormatCtx->streams[v_stream_idx]->codec;
//	//4.���ݱ�����������еı���id���Ҷ�Ӧ�Ľ���
//	AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
//	if (pCodec == NULL)
//	{
//		printf("%s", "�Ҳ���������\n");
//		return -1;
//	}
//
//	//5.�򿪽�����
//	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
//	{
//		printf("%s", "�������޷���\n");
//		return -1;
//	}
//
//	//�����Ƶ��Ϣ
//	printf("��Ƶ���ļ���ʽ��%s", pFormatCtx->iformat->name);
//	printf("��Ƶʱ����%d", (pFormatCtx->duration) / 1000000);
//	printf("��Ƶ�Ŀ�ߣ�%d,%d", pCodecCtx->width, pCodecCtx->height);
//	printf("�����������ƣ�%s", pCodec->name);
//
//	//׼����ȡ
//	//AVPacket���ڴ洢һ֡һ֡��ѹ�����ݣ�H264��
//	//�����������ٿռ�
//	AVPacket *packet = (AVPacket*)av_malloc(sizeof(AVPacket));
//
//	//AVFrame���ڴ洢��������������(YUV)
//	//�ڴ����
//	AVFrame *pFrame = av_frame_alloc();
//	//YUV420
//	AVFrame *pFrameYUV = av_frame_alloc();
//	//ֻ��ָ����AVFrame�����ظ�ʽ�������С�������������ڴ�
//	//�����������ڴ�
//	uint8_t *out_buffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
//	//��ʼ��������
//	avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
//
//	//����ת�루���ţ��Ĳ�����ת֮ǰ�Ŀ�ߣ�ת֮��Ŀ�ߣ���ʽ��
//	struct SwsContext *sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
//		pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_YUV420P,
//		SWS_BICUBIC, NULL, NULL, NULL);
//	int got_picture, ret;
//
//	FILE *fp_yuv = fopen(output, "wb+");
//
//	int frame_count = 0;
//
//	//6.һ֡һ֡�Ķ�ȡѹ������
//	while (av_read_frame(pFormatCtx, packet) >= 0)
//	{
//		//ֻҪ��Ƶѹ�����ݣ�������������λ���жϣ�
//		if (packet->stream_index == v_stream_idx)
//		{
//			//7.����һ֡��Ƶѹ�����ݣ��õ���Ƶ��������
//			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
//			if (ret < 0)
//			{
//				printf("%s", "�������");
//				return -1;
//			}
//
//			//Ϊ0˵��������ɣ���0���ڽ���
//			if (got_picture)
//			{
//				//AVFrameתΪ���ظ�ʽYUV420�����
//				//2 6���롢�������
//				//3 7���롢�������һ�е����ݵĴ�С AVFrame ת����һ��һ��ת����
//				//4 �������ݵ�һ��Ҫת���λ�� ��0��ʼ
//				//5 ���뻭��ĸ߶�
//				sws_scale(sws_ctx, pFrame->data, pFrame->linesize, 0, pCodecCtx->height,
//					pFrameYUV->data, pFrameYUV->linesize);
//
//				//�����YUV�ļ�
//				//AVFrame����֡д���ļ�
//				//data������ͼ���������ݣ���Ƶ�������ݣ�
//				//Y ���� UV ɫ�ȣ�ѹ���ˣ� �˶����ȸ�������
//				//U V ������Y��1/4
//				int y_size = pCodecCtx->width * pCodecCtx->height;
//				fwrite(pFrameYUV->data[0], 1, y_size, fp_yuv);
//				fwrite(pFrameYUV->data[1], 1, y_size / 4, fp_yuv);
//				fwrite(pFrameYUV->data[2], 1, y_size / 4, fp_yuv);
//
//				frame_count++;
//				printf("�����%d֡\n", frame_count);
//			}
//		}
//
//		//�ͷ���Դ
//		av_free_packet(packet);
//	}
//
//	fclose(fp_yuv);
//
//	av_frame_free(&pFrame);
//
//	avcodec_close(pCodecCtx);
//
//	avformat_free_context(pFormatCtx);
//
//
//	return 0;
//}