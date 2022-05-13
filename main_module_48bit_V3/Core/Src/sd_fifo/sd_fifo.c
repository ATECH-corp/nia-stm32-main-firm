#include "sd_fifo.h"
#include <string.h>

struct FIFO{
  uint32_t data;
  uint32_t offset;
  
  struct FIFO *next;
  bool isFull;
};

static struct FIFO _fifo[FIFO_BLK_NUM];
static struct FIFO *_head;

static uint16_t fifo_tmp_head;
static uint16_t fifo_tmp_len;

void FIFO_init(){
  uint16_t i;

  for(i = 0; i < FIFO_BLK_NUM; i++){
    _fifo[i].next = &_fifo[(i + FIFO_BLK_NUM + 1) % FIFO_BLK_NUM];
    _fifo[i].isFull = 0;
    _fifo[i].offset = 0;
    _fifo[i].data = FIFO_START_ADDR + FIFO_BLK_SIZE * i;
  }

  _head = &_fifo[0];

  fifo_tmp_head = 0;
  fifo_tmp_len = 0;
}

static volatile uint16_t _fifo_level_max;
bool FIFO_put(uint8_t* data, uint32_t len){
  
  uint16_t i;
  struct FIFO *f = _head;
  
  for(i = 0; i < FIFO_BLK_NUM; i++){
    if(f->isFull == false) break;
    f = f->next;
  }
 
  if(_fifo_level_max < i) _fifo_level_max = i;
  
  if(i == FIFO_BLK_NUM) return false; // No remaining blk
    
  if(f->offset + len < FIFO_BLK_SIZE){
    memcpy((uint8_t*)(f->data + f->offset), data, len);
    f->offset += len;
  }else{
    uint32_t rem = FIFO_BLK_SIZE - f->offset;
    memcpy((uint8_t*)(f->data + f->offset), data, rem);
    f->offset = 0;
    f->isFull = true;
    f = f->next;
    if(f->isFull == true) return false; // No remaining blk
    f->offset = len - rem;
    memcpy((uint8_t*)f->data, data + rem, f->offset);    
  }
  
  return true;

}

uint8_t* FIFO_get(){ 
  struct FIFO *f;
  if(_head->isFull){
    f = _head;
    _head->isFull = 0;
    _head->offset = 0;
    _head = _head->next;
    return (uint8_t*)f->data;
  }
  
  return 0;
}
