// CS 4318, spring 2018
// Agent Challenge 4: Cricket card game
//
// Here's an example agent function.

#include "ccg.h"

int ccgAgentDefensive(Hand hand, Card lastBowledCard, bool isBatting, const MatchState &match)
{
   Card card;
   int bestCard, bestQuality, quality, whichCard;

   if (isBatting)
   {
      // When batting, play the card with the highest quality according to weighted criteria.
      bestQuality = INT_MIN;
      bestCard = 0;
      for (whichCard = 0; whichCard < numCardsPerHand; whichCard += 1)
      {
         card = hand.getCard(whichCard);
         quality = 0;
         // Favour playing a card that doesn't lose a wicket.
         if (card.getSuit() == lastBowledCard.getSuit() ||
             card.getNumber() >= lastBowledCard.getNumber())
         {
            quality += 100;
         }
         // Have we found a better card to play?
         if (quality > bestQuality)
         {
            bestQuality = quality;
            bestCard = whichCard;
         }
      }
      return bestCard;
   }
   else // is bowling
   {
      // When bowling, play the card with the highest quality according to weighted criteria.
      bestQuality = 0;
      bestCard = 0;
      for (whichCard = 0; whichCard < numCardsPerHand; whichCard += 1)
      {
         card = hand.getCard(whichCard);
         quality = 0;
         // Favour playing a card with a larger number than the last bowled card.
         if (card.getNumber() > lastBowledCard.getNumber())
         {
            quality += 100;
         }
         // Have we found a better card to play?
         if (quality > bestQuality)
         {
            bestQuality = quality;
            bestCard = whichCard;
         }
      }
      return bestCard;
   }
}
