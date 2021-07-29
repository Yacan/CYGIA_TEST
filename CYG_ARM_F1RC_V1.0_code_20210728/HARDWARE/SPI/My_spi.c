#define SPI_SCK_1    GPIO_SetBits(GPIOA, GPIO_Pin_7)            /* SCK = 1 */
#define SPI_SCK_0    GPIO_ResetBits(GPIOA, GPIO_Pin_7)        /* SCK = 0 */

#define SPI_MOSI_1    GPIO_SetBits(GPIOA, GPIO_Pin_6)            /* MOSI = 1 */
#define SPI_MOSI_0    GPIO_ResetBits(GPIOA, GPIO_Pin_6)        /* MOSI = 0 */

#define SPI_READ_MISO    GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)    /* ��MISO����״̬ */

#define Dummy_Byte    0xFF    //��ȡʱMISO���͵����ݣ�����Ϊ��������


//��ʼ��SPI
void SPI_IoInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //SCK��MOSI��CS���ų�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;           //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //MISO���ų�ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;               //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_CS_1;
    SPI_SCK_1;
}

//SPI����ͬʱ��ȡ��д�����ݣ����һ��������������Ҫ��
uint8_t SPI_ReadWriteByte(uint8_t txData)
{
    uint8_t i;
    uint8_t rxData = 0;

    for(i = 0; i < 8; i++)
    {
        SPI_SCK_0;
        delay_us(1);
        //���ݷ���
        if(txData & 0x80){
            SPI_MOSI_1;
        }else{
            SPI_MOSI_0;
        }
        txData <<= 1;
        delay_us(1);

        SPI_SCK_1;
        delay_us(1);
        //���ݽ���
        rxData <<= 1;
        if(SPI_READ_MISO){
            rxData |= 0x01;
        }
        delay_us(1);
    }
    SPI_SCK_0;

    return rxData;
}

uint8_t SPI_ReadByte(void)
{
    return SPI_ReadWriteByte(Dummy_Byte);
}

void SPI_WriteByte(uint8_t txData)
{
    (void)SPI_ReadWriteByte(txData);
}

