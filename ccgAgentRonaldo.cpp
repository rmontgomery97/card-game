// YOUR NAME: Reese Montgomery
//
// CS 4318, spring 2018
// Agent Challenge 4: Cricket card game

#include "ccg.h"

int ccgAgentRonaldo(Hand hand, Card lastBowledCard, bool isBatting, const MatchState &match)
{
   Card card;
   int bestCard, bestQuality, quality, whichCard, runsPossible, difference;
   
   if (isBatting)
   {
      bestQuality = INT_MIN;
      bestCard = 0;
      runsPossible = 0;
      
      if (lastBowledCard.getNumber() >= 9) // if the bowled card is 9 or greater, don't try to score
      {                                    // just play the lowest card of the same suit
         int lowestNum = 12;
         int lowestCard = INT_MIN;
         for (whichCard = 0; whichCard < numCardsPerHand; whichCard += 1)
         {
            if (hand.getCard(whichCard).getNumber() < lowestNum && hand.getCard(whichCard).getSuit() == lastBowledCard.getSuit())
            {
               lowestNum = hand.getCard(whichCard).getNumber();
               lowestCard = whichCard;
            }
         }
         if (lowestCard != INT_MIN)
         {
            return lowestCard;
         }
      }
      
      for (whichCard = 0; whichCard < numCardsPerHand; whichCard += 1)
      {
         card = hand.getCard(whichCard);
         quality = 0;
         
         if (card.getSuit() == lastBowledCard.getSuit()) // if the card is the same suit as the bowled card, look for the one
         {                                               // that scores the most amount of runs           
            quality += 200;
            
            runsPossible = numRuns(card.getNumber() - lastBowledCard.getNumber());
            
            quality += runsPossible * 100;
            
            if (card.getNumber() >= 7 && runsPossible <= 2) // if the card is a higher number and runs possible is low 
            {                                               // try to save it for later
               quality -= 300;
            }
         }
         
         // Have we found a better card to play?
         if (quality > bestQuality)
         {
            bestQuality = quality;
            bestCard = whichCard;
         }
      }
      
      if (bestQuality <= 200) // if the quality of the card with the same suit was low
                              // look for a card with a number >= the bowled card
      {
         for (whichCard = 0; whichCard < numCardsPerHand; whichCard += 1)
         {
            card = hand.getCard(whichCard);
            quality = 0;
            difference = card.getNumber() - lastBowledCard.getNumber();
            
            if (difference == 0) // look for cards equal to or greater than the bowled card's number
            {
               quality += 200;
            }
            else if (difference < 2 && difference > 0)
            {
               quality += 150;
            }
            else if (difference < 4 && difference > 0)
            {
               quality += 100;
            }
            else if (difference < 6 && difference > 0) // try not to play cards a lot higher than the ones bowled since they wont score runs
            {
               quality += 50;
            }
            
            if (quality > bestQuality)
            {
               bestQuality = quality;
               bestCard = whichCard;
            }
         }
      }
      
      if (bestQuality == 0) // if a card STILL hasn't been found, play your lowest numbered card
      {
         int lowestNum = 12;
         int lowestCard = INT_MIN;
         for (whichCard = 0; whichCard < numCardsPerHand; whichCard += 1)
         {
            if (hand.getCard(whichCard).getNumber() < lowestNum)
            {
               lowestNum = hand.getCard(whichCard).getNumber();
               lowestCard = whichCard;
            }
         }
         if (lowestCard != INT_MIN)
         {
            return lowestCard;
         }
      }
      
      return bestCard;
   }
   else // is bowling
   {
      bestQuality = INT_MIN;
      bestCard = 0;
      for (whichCard = 0; whichCard < numCardsPerHand; whichCard += 1)
      {
         card = hand.getCard(whichCard);
         quality = 0;
         if (card.getSuit() == lastBowledCard.getSuit()) // try to play the same suit multiple times in a row
         {
            quality += 100;
         }
         if (card.getNumber() == 11) // try to play higher numbered cards
         {                           // perfect card is same as last suit and an 11 with a score of 200
            quality += 100;
         }
         else if (card.getNumber() >= 9)
         {
            quality += 90;
         }
         else if (card.getNumber() >= 6)
         {
            quality += 60;
         }
         else if (card.getNumber() >= 4)
         {
            quality += 40;
         }
         else if (card.getNumber() >= 2)
         {
            quality += 20;
         }
         
         if (card.getNumber() < 5) {
            for (unsigned whichCard2 = 0; whichCard2 < numCardsPerHand; whichCard2 += 1)
            {
               difference = card.getNumber() - hand.getCard(whichCard2).getNumber();
               if (hand.getCard(whichCard2).getSuit() == card.getSuit() && hand.getCard(whichCard2).getNumber() > card.getNumber())
               {
                  quality += 100;
               }
            }
         }

         if (card.getNumber() == lastBowledCard.getNumber() || (card.getNumber() - lastBowledCard.getNumber() == 1)) // avoid getting "wide" or "bye" calls
         {
            quality = 0;
         }
         
         if (quality > bestQuality)
         {
            bestQuality = quality;
            bestCard = whichCard;
         }
      }
      
      return bestCard;
   }
}

/*

 -I decided to try the same style as the prioritizer agent shown in class. I played the ccg batting practice game 
 multiple times to figure out what kind of pattern would seem to work best. I then created the agent and began to adjust
 the quality numbers until I found the best ones. I found that even small adjustments in the numbers can make a big difference
 in your R/W ratio. While I was playing the batting practice I noticed it was also very difficult to not lose wickets
 when cards of the same suit were played in succession. This made me think to try and play as many cards of the same
 suit in a row as possible.
 
*/
